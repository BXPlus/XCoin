# Week 5: 29th to 5th of December

**Tim**

This week:

This week was also quite busy, but I tried my best to do the max. I had a good first draft of the settings page but I was not happy with it, as there were too many user based infos (which will not be available to store in the type of environment we are currently working in), thus I have decided to take a few step backs and reimplement the page. I think it will be done either by tomorrow or in two days at most. On the github side, we have had a few troubles with merging between members, thus I am trying to solve those problems so that everyone has the same information.

Next week

Finish the settings page for once, as well as start working on the tricount (manager of expenses between users) end of the app, and obviously keep helping members with git.

@salma zainana 

This week i was not able to work on the project for medical reasons. So in this report i am going to talk about what i did on the forth week and what i am planning to do next week. Last week i implemented a code so that we can store our data on a file and i tried to encrypt it. This week i am going to finish  the encryption part, check up on the team updates and discuss on monday my week's objectives with the team leader.]

@Lio 

**This week:**

- Implemented the MD5 function (finished),
- Implementing a test for my function.

**Next week:**

- I am waiting for Cyrus to give me a new task.

**Alex**

**This week:**

- I have made a mistake in the implementation of the contact page so I need to do it again. I didn't build it on a scroll area so this is not practical when having many contacts
- I have added a button for adding a contact but it doesn't work yet

**Next week:**

- Correct this and start implementing the tricount

@Picha 

This week:
I finished the template of the payment page. But we have decided that this payment page won't be a page anymore but a new window so that we can open it from anywhere on the website.

So, I now have to implement a QDialog to create a new window.

Next week:
On my template page, I still have to connect some button together. 

I will continue to make the qdialog window.

@Mamoune Mouchtaki 

@Timothe 

@arthur 

This week I wasn't able to finish the whole design of the balance page but still advanced well on it. II added new things to make the page look better and the names of the contacts in the history of the transactions.

Next week I will try to finish this page and maybe will be able to use the data from the other teams to display the right information on the page.

@Clara  

This week I changed to the Frontend team because of technical problems with CLion. I got familiar with the different pages and the libraries used by the frontend team. 

I started working on the design of the login dialog.

Next week, I will work on the main design.

@Laura Galindo 

This week I mainly analysed in depth the code written by the Blockchain team, to be able to edit it next week. This involved doing some (more) research, and asking specific questions to a fellow team member about his coding of the blockchain.

@Youssef Chaabouni 

This week:

- Added the transaction file: implemented the functions necessary to the implementation of the wallet: getting one's balance and unspent transaction outputs, creating transactions, etc.
- Added targets to the transaction, wallet, and transactionPool files.
- Finalized my part concerning the transactions, wallet and transactionPool work.

Next week:

- Go back to the work I've done at the beginning concerning the Blockchain implementation, and see if there's anything missing & if it's compatible with network implementation.
- If the others are done with their part of the transaction implementation, make sure that transactions can be made between two nodes.
- Work on the Blockchain synchronization between nodes.

@Cyrus Pellet 

This week I reimplemented peer discovery to use a new framework called gRPC. This simplifies exchanges between nodes and replaces Drogon's client/server architecture. I fully implemented ping handshakes, DNS syncs, local saves, and started implementing header/block sync. Next week I will finish all this and create the SDK for the UI team.

@Malo 

This week I finished the implementation of the key class and the functions sign() and verify(). I faced many problems such as format conversion with openssl types.

Next week I will complete wallet and transaction with functions implemented with keys.

@Kevin Messali

This week I started to implement a very naive way of synchronizing the blockchain using the header first sync manner. I added it on the new implementation of the network connection protocol called gRPC.

Next week I will finalize the header sync and make it production ready.

@Thang Long VU 

This week:

- Fix remaining bugs in transaction.cpp and transaction.h (https://github.com/BXPlus/XCoin/commit/feec0fe5ce4eb0bca91bb86c8f2e40060e8008e6)
- Implemented hasDuplicates in transaction.cpp (https://github.com/BXPlus/XCoin/commit/f77333b4db9f71311cc7068bf886bc65b4fd7bd4)
- Implemented validateBlockTransactions in transaction.cpp (https://github.com/BXPlus/XCoin/commit/876ebef534405e6f07dee9f5e84f49cf3ef182d7)
- Implemented processTransactions in transaction.cpp (https://github.com/BXPlus/XCoin/commit/a23cb7e2efdc2d83f0045b3121f14f723356caec)

Next week:

- Write tests for transaction.cpp, aiming for at least 90% coverage.


@Jean-Sebastien G. 

This week I started implementing the wallet on CLion but it crashed and then shifted to working on the implementation on QT creator. I cannot commit using Qt creator so I was trying to find new solutions to commit onto the Github

Next week we should have finished the wallet implementation and will most likely write tests for the wallet

@Timothe

This week I helped implement the wallet part of the coin implemented the functions that are necessary for the transactions.
Next week I will look over what the Frontend team worked on in order to prepare the merge, try to fix issues if there are any and write some tests if need be.
