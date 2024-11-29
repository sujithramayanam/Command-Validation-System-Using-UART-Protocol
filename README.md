# Command-Validation-System-Using-UART-Protocol
This application is developed for a secure access control system that communicates with external devices through UART. The system is designed to validate and process incoming messages, which must follow a specific format that includes a passkey and command content. The message format is:

@#passkey#message content$
@#: Marks the start of the message.
passkey: A 4-character security code (valid key: "8675").
message content: The actual command (e.g., "Unlock Door", "Lock Door").
$: Marks the end of the message.

The system will:

Process the message if it starts with @#, ends with $, and has the correct passkey.
Reject the message with an error if the format or passkey is incorrect.

Requirements
Keil μVision IDE for ARM 
Example Message:
Valid Message: @#8675#Unlock Door$
Invalid Message (incorrect passkey): @#1234#Unlock Door$
Invalid Message (incorrect format): @#8675Unlock Door$
