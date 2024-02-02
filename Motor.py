import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32

class MotorControlNode(Node):
    def __init__(self):
        super().__init__('motor_control_node')

        # Initialize ROS2 parameters, publishers, subscribers, etc.
        self.left_motor_sub = self.create_subscription(Float32, 'left_motor_cmd', self.left_motor_callback, 10)
        self.right_motor_sub = self.create_subscription(Float32, 'right_motor_cmd', self.right_motor_callback, 10)

        # Initialize motor control variables
        self.left_motor_cmd = 0.0
        self.right_motor_cmd = 0.0

    def left_motor_callback(self, msg):
        # Update left motor command
        self.left_motor_cmd = msg.data
        self.get_logger().info('Left Motor Command: %.2f' % self.left_motor_cmd)

        # Call function to send motor command to the left motor
        self.send_left_motor_command()

    def right_motor_callback(self, msg):
        # Update right motor command
        self.right_motor_cmd = msg.data
        self.get_logger().info('Right Motor Command: %.2f' % self.right_motor_cmd)

        # Call function to send motor command to the right motor
        self.send_right_motor_command()

    def send_left_motor_command(self):
        # Implement logic to send the left motor command to the motor controller
        # This could involve communicating with the motor driver or publishing to another topic
        # For this example, it just prints the command
        self.get_logger().info('Sending Left Motor Command: %.2f' % self.left_motor_cmd)

    def send_right_motor_command(self):
        # Implement logic to send the right motor command to the motor controller
        # This could involve communicating with the motor driver or publishing to another topic
        # For this example, it just prints the command
        self.get_logger().info('Sending Right Motor Command: %.2f' % self.right_motor_cmd)

def main(args=None):
    rclpy.init(args=args)
    node = MotorControlNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
  
