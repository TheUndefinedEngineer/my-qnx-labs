# Experiment 8 Detail

## Aim
To implement client–server communication using the name lookup mechanism in QNX
Neutrino RTOS, where the client finds the server using a registered name instead of PID and CHID, sends a pulse and message, and receives the checksum reply.

## My Thought Process
Regular IPC requires the client to know the server's PID and CHID beforehand, which adds complexity since the server must always run first and share those values explicitly. This is where the name lookup mechanism in QNX comes into picture.

Name lookup uses name_attach() to register a channel under a human-readable name, which any client can connect to using `name_open()` - no PID or CHID needed. This adds a small overhead from the name resolution but significantly reduces coupling between the two processes.

The server still needs to run first to register the name. If the client calls `name_open()` before the server has registered, it will fail immediately. Once connected, if the server goes down, subsequent pulses and messages from the client will be dropped silently.

## Algorithm
1. Start the program.
2. Run the server program first.
3. The server registers itself with a name ("server") using `name_attach()`.
4. The OS creates a channel internally and associates it with the given name.
5. The server enters an infinite loop and waits for communication using `MsgReceive()`.
6. Run the client program.
7. The client connects to the server using name_open("server", 0) and obtains a Connection ID (coid).
8. The client prepares a message containing the string "Mohan Sai".
9. The client sends a pulse using MsgSendPulse() with:
10. pulse code = 3
11. pulse value = `0xC0DEBEEF`
12. The server receives the pulse using `MsgReceive()`.
13. If `rcvid == 0`, the server identifies it as a pulse:
14. If it is a disconnect pulse (`_PULSE_CODE_DISCONNECT`), it prints “Client
disconnected”
15. Otherwise, it prints:
16. “Pulse Received, Client active!”
17. Pulse code and pulse value
18. The client sends a message using `MsgSend()`.
19. The server receives the message (`rcvid > 0`) and extracts the string.
20. The server computes the checksum using `calculate_checksum()`.
21. The server sends the checksum back using `MsgReply()`.
22. The client receives the checksum and displays it.
23. The client closes the connection using `name_close()`.
24. The server continues waiting for further pulses and messages.

## Result
Successfully implemented IPC communication mechanism between a server and a client using the functions `name_attach()`, `name_detach()`, `name_open()`, and `name_close()`.

## Key Learning Outcomes
- Basic understanding of message-based Inter-Process Communication (IPC). 
- The use of the functions - `name_attach()`, `name_detach()`, `name_open()`, and `name_close()`.
- Better understanding of client-server relationship and working.
