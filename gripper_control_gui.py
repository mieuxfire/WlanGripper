import tkinter as tk
from paho.mqtt import client as mqtt_client

# MQTT configuration
broker = 'localhost'  # Change to your broker IP if not running locally
port = 1883           # MQTT port
control_topic = 'gripper/control'
position_topic = 'gripper/position'

# Create a new instance of the MQTT client
client = mqtt_client.Client()

def connect_mqtt():
    """Connect to the MQTT broker."""
    try:
        client.connect(broker, port)
        client.loop_start()
        subscribe_position()
        update_connection_info("Connected", broker, "green")
    except Exception as e:
        update_connection_info(f"Connection Failed: {e}", broker, "red")

def publish(message):
    """Publish a message to the specified topic."""
    client.publish(control_topic, message)

def open_gripper():
    """Function to open the gripper."""
    publish('0')  # Send '0' to open the gripper

def close_gripper():
    """Function to close the gripper."""
    publish('1')  # Send '1' to close the gripper

def subscribe_position():
    """Subscribe to the gripper position topic."""
    client.subscribe(position_topic)

def on_message(client, userdata, msg):
    """Callback function when a message is received."""
    position = msg.payload.decode()
    position_label.config(text=f"Current Gripper Position: {position}")

def update_connection_info(status, broker_ip, color):
    """Update the connection status and broker IP in the GUI."""
    connection_status_label.config(text=f"Connection Status: {status}")
    broker_info_label.config(text=f"Broker: {broker_ip}")
    # Update the LED indicator color
    led_canvas.config(bg=color)

# Set up the MQTT message callback
client.on_message = on_message

# Create the main application window
app = tk.Tk()
app.title("Gripper Control")

# Connection information labels
connection_status_label = tk.Label(app, text="Connection Status: Connecting...")
connection_status_label.pack(pady=5)

broker_info_label = tk.Label(app, text=f"Broker: {broker}")
broker_info_label.pack(pady=5)

# LED indicator for connection status
led_canvas = tk.Canvas(app, width=20, height=20, bg='red')  # Start as red
led_canvas.pack(pady=5)

# Create buttons for opening and closing the gripper
open_button = tk.Button(app, text="Open Gripper", command=open_gripper)
open_button.pack(pady=10)

close_button = tk.Button(app, text="Close Gripper", command=close_gripper)
close_button.pack(pady=10)

# Label to display the current position
position_label = tk.Label(app, text="Current Gripper Position: Unknown")
position_label.pack(pady=10)

# Start the MQTT connection and subscription
connect_mqtt()

# Start the GUI event loop
app.mainloop()

# Stop the MQTT loop when the GUI is closed
client.loop_stop()
client.disconnect()
