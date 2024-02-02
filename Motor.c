#include <stdio.h>
#include <std_msgs/msg/float32.h>
#include <rcl/rcl.h>

typedef struct {
  float motor_cmd;
  rcl_publisher_t left_motor_pub;
  rcl_publisher_t right_motor_pub;
} MotorControlNode;

void left_motor_callback(const void *msgin) {
  const std_msgs__msg__Float32 *msg = (const std_msgs__msg__Float32 *)msgin;
  printf("Left Motor Command: %.2f\n", msg->data);

  // Implement logic to send the left motor command to the motor controller
  // This could involve communicating with the motor driver or publishing to another topic
  // For this example, it just prints the command
}

void right_motor_callback(const void *msgin) {
  const std_msgs__msg__Float32 *msg = (const std_msgs__msg__Float32 *)msgin;
  printf("Right Motor Command: %.2f\n", msg->data);

  // Implement logic to send the right motor command to the motor controller
  // This could involve communicating with the motor driver or publishing to another topic
  // For this example, it just prints the command
}

int main(int argc, char *argv[]) {
  rcl_init_options_t options = rcl_get_zero_initialized_init_options();
  rcl_context_t context = rcl_get_zero_initialized_context();
  rcl_init_options_init(&options, rcl_get_default_allocator());
  rcl_init(argc, argv, &options, &context);

  rcl_node_t node = rcl_get_zero_initialized_node();
  const char *node_name = "motor_control_node";
  const char *namespace = "";
  rcl_node_init(&node, node_name, namespace, &context);

  rcl_subscription_t left_motor_sub = rcl_get_zero_initialized_subscription();
  const char *left_motor_topic = "left_motor_cmd";
  rcl_subscription_init(&left_motor_sub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32), left_motor_topic, rcl_subscription_get_default_options());

  rcl_subscription_t right_motor_sub = rcl_get_zero_initialized_subscription();
  const char *right_motor_topic = "right_motor_cmd";
  rcl_subscription_init(&right_motor_sub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32), right_motor_topic, rcl_subscription_get_default_options());

  MotorControlNode motor_node = {
    .motor_cmd = 0.0,
    .left_motor_pub = rcl_publisher_get_zero_initialized_publisher(),
    .right_motor_pub = rcl_publisher_get_zero_initialized_publisher()
  };

  // Set up publishers (not shown in this example)

  rcl_callback_group_t callback_group = rcl_get_zero_initialized_callback_group();
  rcl_subscription_set_callback_group(&left_motor_sub, &callback_group);
  rcl_subscription_set_callback_group(&right_motor_sub, &callback_group);

  while (rcl_ok()) {
    rcl_wait_set_t wait_set = rcl_get_zero_initialized_wait_set();
    rcl_wait_set_init(&wait_set, 2, 0, 0, 0, 0, rcl_get_default_allocator());

    rcl_wait_set_clear(&wait_set);
    rcl_wait_set_add_subscription(&wait_set, &left_motor_sub, NULL);
    rcl_wait_set_add_subscription(&wait_set, &right_motor_sub, NULL);

    rcl_wait(&wait_set, RCL_MS_TO_NS(100));

    if (rcl_wait_set_is_ready(&wait_set)) {
      rcl_ret_t ret;
      std_msgs__msg__Float32 msg;
      ret = rcl_take(&left_motor_sub, &msg, NULL, NULL);
      if (RCL_RET_OK == ret) {
        motor_node.m
