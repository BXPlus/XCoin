# Week 4: 22nd to 28th of November

**Tim**

This week:

I did not work as much this week as I did in the previous weeks: it was a very dense one for me (exchanges, tests, personal work, etc..). So, I did not reach my goal of finishing the settings page, but still made some progress on it style wise. For the github side, I also helped merge the branches of the frontend team in the main frontend branch, and of course helped members when they had trouble with git. 

Next week:

Now I just need to make the settings page functional and add information such as showing the root DNS address, full/night node, public address, and public address, etc... I would also like to make it possible to add a feature where the client can change the look by clicking on a button (dark/light mode). Next week, the settings page is finally done!

**Alex**

This week: I tested out some layouts for the welcome page of the app: grid layouts for graphic displays, a scroll-type layout, etc. However, we decided that for now, while the coins have no "currency", it is not necessary nor possible to display graphics on the welcome page. Moreover, I started the implementation of the contacts page.

Next week: I will continue the implementation of the overall layout of the contacts page and maybe implement a "tricount" for the app. A tricount is an agenda used to keep track of payments in a group of people, and allows to see balance and ease payments in a large group of people. (It is an extra feature of the app).

@Lio 

**This week:**
- Did research on MD5 hashing

**Next week:**
- Implement MD5 hashing

@Picha 

This week:

I worked on the template page of "BUY XCOIN". 

I did many researches about new classes of the qt library so that we can create a solid webpage.

I fixed some issues that I encountered with github.

Next week:

I'll finish the template of BUY XCOIN and start to work on the template of the page for "PAY WITH XCOIN". As @Alex mentioned, we will try to implement a tricount algorithm on this page.

@Mamoune Mouchtaki 

This week I did not reach my goal of ending my graph function. I have some issues on it so I did some research to try to figure it out how to fix them. For the next week, I want to finish it then I will talk to the front end team to help them on something else.

@Timothe 

This week I did some research on how to implement the sha256 function using the OpenSSL library we implemented. Then I created a new function using the OpenSSL library tools and made sure it worked well with all its uses in the project. Next week I will focus more on the wallet part of the coin.

@arthur 

This week, I did more research on functions and libraries that could make the 'balance' page look better. Using what I learned about, I worked and advanced on the design of this page, have a scrolling bar for the recent transactions and so on. 

Next week, I will continue and try to finish the design of the pages. We will also try to work on a tricount system.

@Clara  

This week, I had some compilation problems on CLion; we tried to fix it by installing CMake again and brew but it did not work out. 

@Laura Galindo 

Until Monday I had a compilation problem on CLion, so I could not run the project anymore. We solved it on Monday, although I am now using Visual Studio instead.

I looked at my collegues' code to understand it in depth (the parts concerning generating blocks and validating timestamps specifically), and I started to try to implement some of the countermeasures (currently exploring forbidding modifying timestamps and context-aware transactions).

Next week I will continue doing this. 

@Youssef Chaabouni 

This week:

- Added the missing functions necessary for the transaction implementation.
- Fixed errors in the wallet & transactions files.
- Completed the implementation of Transaction Pool and its related functions.
- Added targets to the transaction & transactionPool files.
- Commented the transaction file so that the code compiles. Waiting for the errors to be fixed.

Next week:

- Work on the wallet implementation
- Try to fix and finalize the transaction part
- By the end of next week, make sure that transactions can be made between two nodes

@Cyrus Pellet 

This week I refactored the interface class to support more message types. More importantly, I co-developed the new XNode class architecture, which now supports syncing handshakes with a server running on a separate thread from the client. This now allows us to send syncing messages for headers, DNS maps, and private address lookups.

Next week I will finalize blockchain sync, test the peer discovery and make sure transactions are done and working between two nodes. I will also implement the SDK for the front-end team.

@Malo 

This week I defined new functions to the key class: keyFromPrivate() and keyFromPublic(). I also built the peer discovery architecture in the node class up to the communication with other nodes and the DNS seed. Next week I will make the sign() function of the ECDSA protocol and test if the key class works as expected. I will also implement the Wallet.

@Kevin Messali 

This week I finished fixing the web socket implementation, and discussed with @Cyrus Pellet about the challenges that we were encountering with our network implementation with servers and clients. We came together to the fact that we needed to use multi-threading to be able to achieve a bidirectional communication (nodes are both client and server now). So we implemented it and re-factorized the XNode architecture to implement a network in a decentralized fashion.

Next week, I pursue my implementation of header-first sync for the blockchains and merge the peer @Malo's peer discovery in the network.
