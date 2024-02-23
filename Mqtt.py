import rclpy
from rclpy.node import Node
import paho.mqtt.client as mqtt

class AutonomousRobotNode(Node):
    def __init__(self):
        super().__init__('autonomous_robot_node')

        # Initialize ROS2 parameters, publishers, subscribers, etc.

        # Initialize MQTT client for cloud communication
        self.mqtt_client = mqtt.Client()
        self.mqtt_client.on_connect = self.on_mqtt_connect
        self.mqtt_client.on_message = self.on_mqtt_message

        # Connect to the MQTT broker (replace 'mqtt.eclipse.org' with your broker address)
        self.mqtt_client.connect('mqtt.eclipse.org', 1883, 60)
        self.mqtt_client.loop_start()

    def on_mqtt_connect(self, client, userdata, flags, rc):
        self.get_logger().info('Connected to MQTT broker with result code %d' % rc)

        # Subscribe to topics or perform other actions on connection

    def on_mqtt_message(self, client, userdata, msg):
        # Handle incoming messages from the cloud
        message_payload = msg.payload.decode('utf-8')
        self.get_logger().info('Received message: %s' % message_payload)

        # Process the message and take appropriate actions

    def cleanup(self):
        # Perform cleanup tasks when the node is shutting down
        self.mqtt_client.disconnect()
        self.mqtt_client.loop_stop()

def main(args=None):
    rclpy.init(args=args)
    node = AutonomousRobotNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    node.cleanup()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
  
