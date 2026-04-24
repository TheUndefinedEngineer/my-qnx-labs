# Experiment 6 Detail

## Aim
To implement the Send–Receive–Reply communication mechanism between a client and server process in QNX Neutrino RTOS, where the client sends a string message to the server and the server calculates and returns the checksum of the received string using message passing functions such as ChannelCreate(), ConnectAttach(), MsgSend(), MsgReceive(), and MsgReply().

## My Thought Process
The requirement is a synchronous, bidirectional exchange between two processes - the client sends data and needs a processed result back. MsgSend(), MsgReceive(), and MsgReply() is the natural fit since MsgSend() blocks the client until the server explicitly replies, guaranteeing the client always gets a response.

The server must run first because it owns the channel - the client needs the server's PID and CHID to call ConnectAttach(). Writing these to `/tmp/server_chid.txt` is a simple runtime rendezvous without hardcoding.

The server loops indefinitely after replying so it can serve multiple clients, while the client terminates once it receives its result - reflecting a typical service-consumer pattern.

## Algorithm
    1. Start the program.
    2. Execute the server program first.
    3. The server creates a communication channel using ChannelCreate() and obtains the Channel ID (CHID).
    4. The server retrieves its Process ID (PID) using getpid().
    5. The server displays the PID and CHID on the console.
    6. The server writes the PID and CHID to a file (/tmp/server_chid.txt) so that the client can access them.
    7. The server enters an infinite loop and waits for a client message using MsgReceive().
    8. Execute the client program.
    9. The client opens /tmp/server_chid.txt and reads the server PID and CHID.
    10. The client prepares a message structure containing the string:
    11. "Client and Server".
    12. The client establishes a connection to the server using ConnectAttach() and obtains a Connection ID (coid).
    13. The client sends the message to the server using MsgSend() and blocks while waiting for a reply.
    14. The server receives the message using MsgReceive() and obtains the receive ID (rcvid).
    15. The server processes the received string and computes its checksum using calculate_checksum().
    16. The server sends the computed checksum back to the client using MsgReply().
    17. The client receives the checksum returned by the server.
    18. The client displays the checksum on the screen.
    19. The server continues running and waits for messages from other clients.
    20. The client program terminates after displaying the result.

## Result
Successfully implemented SEND-RECEIVE-REPLY communication mechanism between a server and a client using the functions MsgSend(), MsgReceive(), MsgReply, ChannelCreate(), and ConnectAttach().

## Key Learning Outcomes
- Basic understanding of message-based Inter-Process Communication (IPC). 
- The use of the functions - MsgSend(), MsgReceive(), MsgReply, ChannelCreate(), and ConnectAttach()
- Better understanding of client-server relationship and working.
