# Simple SMTP Mail Server

This is a simple implementation of an SMTP (Simple Mail Transfer Protocol) server written in C. It demonstrates basic networking, text-based communication, and command parsing.

## Features

- Supports basic SMTP commands:
  - `HELO`
  - `MAIL FROM`
  - `RCPT TO`
  - `DATA`
  - `QUIT`
- Sends basic responses to the client.
- Handles a single client connection at a time.

## Prerequisites

To compile and run this project, you'll need:

- GCC or any C compiler
- A Linux/Unix-based system or Windows with socket programming support
- Telnet (for testing the server)

## Installation and Usage

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/simple-smtp-server.git
   cd simple-smtp-server
   ```

2. Compile the source code:

   ```bash
   gcc mailserver.c -o mailserver
   ```

3. Run the server:

   ```bash
   ./mailserver
   ```

   The server will start listening on port `2525`.

4. Test the server using `telnet`:

   ```bash
   telnet localhost 2525
   ```

5. Use basic SMTP commands to interact with the server:

   ```
   HELO example.com
   MAIL FROM: <sender@example.com>
   RCPT TO: <recipient@example.com>
   DATA
   This is a test email.
   .
   QUIT
   ```

## Example Interaction

Below is an example session between the client (telnet) and the server:

```
220 Simple Mail Server

HELO example.com
250 Hello

MAIL FROM: <sender@example.com>
250 OK

RCPT TO: <recipient@example.com>
250 OK

DATA
354 End data with <CR><LF>.<CR><LF>

This is a test email.
.
250 Message accepted

QUIT
221 Bye

Connection closed by foreign host.
```

## Limitations

- The server does not store emails.
- No encryption (e.g., SSL/TLS) is implemented.
- Only handles one client connection at a time (no concurrency).
- Not fully compliant with the SMTP protocol.

## Future Improvements

- Add email storage using file I/O or a database.
- Implement concurrency to handle multiple clients simultaneously.
- Support encryption (SSL/TLS) for secure communication.
- Improve protocol compliance with advanced SMTP features.

## License

This project is open-source and available under the [MIT License](LICENSE).

---
