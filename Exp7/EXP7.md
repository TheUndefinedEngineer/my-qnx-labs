# Experiment 7 Detail

## Aim
To implement pulse-based and message-based Inter-Process Communication (IPC) between a client and server in QNX Neutrino RTOS, where the client sends a pulse and a string message to the server and the server processes the pulse and returns the checksum of the received string.

## My Thought Process
The core requirement is for one process to notify another without blocking the sender. A pulse is the natural fit here — it's a fixed-size, non-blocking IPC primitive in QNX Neutrino, meaning the client can fire-and-forget without waiting for the server to process it.

For the message part, MsgSend() is used because the client needs a response (the checksum), making it a blocking, synchronous exchange — appropriate when a reply is expected.

Since both programs run as separate executables, the server's PID and CHID need to be shared at runtime. Writing them to /tmp/server_chid.txt is a simple, filesystem-based rendezvous that avoids hardcoding values.

The rcvid return value from MsgReceive() acts as a natural discriminator — 0 means a pulse arrived, a positive value means a message arrived — allowing a single receive loop to handle both IPC types cleanly.


## Algorithm
1. Start the program.
2. Run the server program first.
3. The server creates a communication channel using ChannelCreate() and obtains theChannel ID (CHID).
4. The server retrieves its Process ID (PID) using getpid() and displays both PID and CHID.
5. The server writes the PID and CHID to a file (/tmp/server_chid.txt) for client access.
6. The server enters an infinite loop and waits for communication using MsgReceive().
7. Run the client program.
8. The client reads the server PID and CHID from /tmp/server_chid.txt.
9. The client establishes a connection to the server using ConnectAttach() and obtains a Connection ID (coid).
10. The client sends a pulse to the server using MsgSendPulse() with:
11. pulse code = 1
12. pulse value = 0xDEADBEEF
13. The server receives the pulse using MsgReceive().
14. If rcvid == 0, the server identifies the received data as a pulse and prints:
15. “Client active...”
16. Pulse code and pulse value
17. The client then sends a message containing the string "Client and Server" using MsgSend().
18. The server receives the message (rcvid > 0) and processes the string.
19. The server computes the checksum using calculate_checksum().
20. The server sends the checksum back to the client using MsgReply().
21. The client receives the checksum reply and displays the result.
22. The server continues waiting for both pulses and messages from clients.
23. The client program terminates after displaying the checksum.

## Result
Successfully implemented pulsed-based communication mechanism between a server and a client using the functions MsgSendPulse(), MsgReceive(), ChannelCreate(), and ConnectAttach().

## Key Learning Outcomes
- Basic understanding of pulse-based Inter-Process Communication (IPC).
- The use of the functions - MsgSendPulse(),MsgSend(), MsgReceive(), MsgReply(), ChannelCreate(), and ConnectAttach().
- How to use `rcvid` return values to differentiate messages and pulses.
- Better understanding of message-based Inter-Process Communication (IPC).
