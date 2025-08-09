#include "smart_can_stuff/pid_controller.hpp" // PID kontrolcüsü sınıfı başlık dosyası

using std::placeholders::_1; // Callback fonksiyonları için placeholder

namespace hmk_pid_control
{
PIDController::PIDController(const rclcpp::NodeOptions & options)
: Node("steering_pid_node", options), // ROS 2 düğümünün adını ve seçeneklerini ayarla

  m_derivative_error(0), // Başlangıç değerlerini sıfırla
  m_previous_error(0),
  m_error(0),
  m_integral_error(0),
  m_set_value(0),
  m_output(0),
  m_feedback_value(0),
  m_previous_pid_time(0),
  m_previous_set_value(0),
  m_target_data_since_lastcb(0)
{
    declare_parameter<double>("kp", 10.0);
    declare_parameter<double>("ki", 2.0);
    declare_parameter<double>("kd", 0.0);
    declare_parameter<double>("kff", 0.0);
    declare_parameter<double>("min_output", 0.0);
    declare_parameter<double>("max_output", 255.0);
    declare_parameter<std::string>("set_value_topic", "/beemobs/steering_target_value");
    declare_parameter<std::string>("feedback_value_topic", "/beemobs/FeedbackSteeringAngle");
    declare_parameter<std::string>("output_topic", "/beemobs/AUTONOMOUS_SteeringMot_Control");
    declare_parameter<int>("timeout_threshold", 3);

    if (!readParameters()) // Parametreleri oku ve doğrula
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to read parameters. Shutting down node.");
        rclcpp::shutdown(); // Parametre okunamazsa düğümü kapat
    }
    else
    {
        RCLCPP_INFO(this->get_logger(), "Successfully launched node.");
    }

    // Setpoint mesajlarını almak için abonelik oluştur
    m_set_value_subscriber = this->create_subscription<std_msgs::msg::Float64>(
        m_set_value_topic, 10, std::bind(&PIDController::setValueCallback, this, _1));

    // Feedback mesajlarını almak için abonelik oluştur
    m_feedback_value_subscriber = this->create_subscription<smart_can_msgs::msg::Feedbacksteeringangle>(
        m_feedback_value_topic, 10, std::bind(&PIDController::feedbackValueCallback, this, _1));

    // Çıktı mesajlarını yaymak için yayımcı oluştur
    m_output_publisher = this->create_publisher<smart_can_msgs::msg::Autonomoussteeringmotcontrol>(
        m_output_topic, 10);
}

bool PIDController::readParameters()
{
    // Parametreleri ROS 2 parametre sunucusundan oku
    // Eğer parametreleri okuyamazsa, hata mesajı yazdır ve false döndür
    if (!this->get_parameter("kp", m_kp))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'kp'");
        return false;
    }
    if (!this->get_parameter("kd", m_kd))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'kd'");
        return false;
    }
    if (!this->get_parameter("ki", m_ki))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'ki'");
        return false;
    }
    if (!this->get_parameter("kff", m_kff))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'kff'");
        return false;
    }
    if (!this->get_parameter("min_output", m_min_output))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'min_output'");
        return false;
    }
    if (!this->get_parameter("max_output", m_max_output))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'max_output'");
        return false;
    }
    if (!this->get_parameter("set_value_topic", m_set_value_topic))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'set_value_topic'");
        return false;
    }
    if (!this->get_parameter("feedback_value_topic", m_feedback_value_topic))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'feedback_value_topic'");
        return false;
    }
    if (!this->get_parameter("output_topic", m_output_topic))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'output_topic'");
        return false;
    }
    if (!this->get_parameter("timeout_threshold", m_timeout_threshold))
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to get param 'timeout_threshold'");
        return false;
    }

    return true; // Tüm parametreler başarıyla okunmuşsa true döndür
}

void PIDController::setValueCallback(const std_msgs::msg::Float64::SharedPtr t_set_value)
{
    // Gelen setpoint değerini güncelle ve zaman aşımı sayacını sıfırla
    m_set_value = t_set_value->data;
    m_target_data_since_lastcb = 0;
}

void PIDController::feedbackValueCallback(const smart_can_msgs::msg::Feedbacksteeringangle::SharedPtr t_feedback_value)
{
    // Gelen feedback değerini güncelle
    m_feedback_value = t_feedback_value->feedbacksteeringangle;
    if (m_target_data_since_lastcb < m_timeout_threshold)
    {
        controlLoop(); // Kontrol döngüsünü çalıştır
        sendToTopic(); // Çıktı mesajını yay
        if (m_timeout_threshold - m_target_data_since_lastcb == 1)
        {
            // Zaman aşımı durumunda motoru durdurmak için mesaj gönder
            smart_can_msgs::msg::Autonomoussteeringmotcontrol msg;
            msg.autonomous_steeringmot_pwm = 0;
            msg.autonomous_steeringmot_en = 0;
            m_output_publisher->publish(msg);
        }
    }
    m_target_data_since_lastcb += 1; // Zaman aşımı sayacını artır
}

void PIDController::controlLoop()
{
    // PID kontrol döngüsünü implement etmek için gerekli fonksiyon
    double now = this->now().seconds(); // Şu anki zamanı al
    double pid_dt_duration = now - m_previous_pid_time; // Zaman farkını hesapla

    m_error = m_set_value - m_feedback_value; // Hata hesapla

    m_integral_error += m_error * pid_dt_duration; // Integral hatasını hesapla
    m_derivative_error = (m_error - m_previous_error) / pid_dt_duration; // Türev hatasını hesapla

    m_output = m_kp * m_error + m_ki * m_integral_error + m_kd * m_derivative_error + m_kff * m_set_value; // PID formülü

    // Çıkışı sınırla ve integral hatasını güncelle
    if (m_output > m_max_output)
    {
        m_output = m_max_output;
        m_integral_error -= m_error * pid_dt_duration;
    }
    if (m_output < m_min_output)
    {
        m_output = m_min_output;
        m_integral_error -= m_error * pid_dt_duration;
    }

    // Setpoint değişikliği durumunda integral hatasını sıfırla
    if (m_previous_set_value * m_set_value < 0)
    {
        m_integral_error = 0;
    }
    else
    {
        m_previous_set_value = m_set_value;
    }

    // Önceki hata ve zamanı güncelle
    m_previous_error = m_error;
    m_previous_pid_time = now;
}

void PIDController::sendToTopic()
{
    // Çıktı mesajını oluştur ve yay
    smart_can_msgs::msg::Autonomoussteeringmotcontrol msg;
    if (m_feedback_value != m_set_value)
    {
        if (m_output > 0)
        {
            msg.autonomous_steeringmot_pwm = static_cast<uint8_t>(128 + (m_output / m_max_output) * 127);
            msg.autonomous_steeringmot_en = 1;
        }
        else  
        {
            msg.autonomous_steeringmot_pwm = static_cast<uint8_t>((m_output / m_min_output) * 127);
            msg.autonomous_steeringmot_en = 1;
        }
    }
    else
    {
        msg.autonomous_steeringmot_pwm = 0;
        msg.autonomous_steeringmot_en = 0;
    }
    m_output_publisher->publish(msg); // Mesajı yay
}

} // namespace hmk_pid_control

