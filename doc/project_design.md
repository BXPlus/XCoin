# Project design brief

# Functionality

- XCoin is a green cryptocurrency, that uses energy-efficient verification algorithm to make transaction in a decentralized fashion.
    - Users are able to send and receive coins through the app.
- Use PKC (Public-Key Cryptography) to validate the authenticity of the transations using asymetric encryption (RSA-like).
    - Public Key is used to received money, it will be the address of the user, therefore it has to be known by the sender.
    - Private Key is used to unlock the transaction and access the fund, it is used to proved ownership.
- The following will be implemented in game-like manner in order to enhance the user experience and make it more enjoyable.
    - The user will have the possibility to consult his balance and therefore own a wallet (first digital, maybe physical in the future).
    - In the sofware the user enters the address of the recipient and sends money. It will be removed obviously only if the transaction is verified (block created and verified, broadcast the blockchain to all users, etc).
    - The user will receive a notification when receiving funds, and therefore it applies automatically his private key and this would validate the transaction.

# Deadlines and deliverables

Deadlines & deliverables will be issued in parallel **independently** for the **Core** branch (Blockchain/API/Security) and the **User** branch (Frontend/Currency). The main stages are as follows:

**Core:**

1. Core blockchain completion
2. Blockchain security hardening
3. API completion
4. Currency definition integration
5. Machine learning verification for transactions

**User:**

1. Desktop app UI mokups
2. UI integrated with SDK and API
3. Refining and UX improvements
4. Additional practical features: address book, tricount, ...

An updated roadmap can be found at [https://www.notion.so/bx23/87a4ced028c745d6aa1b57f3beb4b8ed?v=dcea925d05254224bf2d4c3f37af0820](https://www.notion.so/87a4ced028c745d6aa1b57f3beb4b8ed)

# Software architecture

The project architecture is divided into two branches (**Core**/**User**)
