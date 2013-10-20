about core
----------
the core will start 2 process, one for listen, another for dealing message.

![core](https://rawgithub.com/duguying/ichat/master/docs/core.svg)

- about message

the father process received messages and send to the son process via pipe, and the son parse the message, the father read message from queue and send the message to the user.

- about pipe

we should create Two-way communication pipe. Create two pipe, one for receiving, another for sending.