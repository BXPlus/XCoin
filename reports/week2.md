# Week 2: 8th to 14th of November

@Cyrus Pellet

This week I had a close look at how to optimise data transfers between nodes and I came up with a couple of ideas to explore in that regard. There is an idea of full and light nodes, the latter needing to keep less data to work. I explored Google’s protobuf standard for replacing json and did some tests in cpp. I also worked on package management with Kevin and spent a lot of time fixing cmake configurations so that they still work across multiple platforms and architectures.

Next week I will finish my protobuf interchange classes and will work on some more unit tests for the networking and blockchain. I will also implement some local node caching depending on the other teams progress.

@Youssef Chaabouni 

This week: - Defined the basics of the Transaction object (txIns and txOuts).
           - Chose and learned about an encryption process to use: elliptic functions cryptography and ecdsa.
           - Implemented the transactionPool to manage unconfirmed transactions.
           - Implemented a tool to update the transactionPool.

Next week: - Will work on validating transactions before adding them to the transactionPool.
           - Will work on moving the transactions from the transactionPool into the Blockchain.

@Kevin Messali 

This week I found [vcpkg](https://github.com/microsoft/vcpkg), a library manager and decided to implement it to our project, especially when dealing with dependencies. Indeed, I have spent around 8h in total trying to add drogon, our library for networking and websockets. With @Cyrus Pellet we have set up [vcpkg](https://github.com/microsoft/vcpkg), added it as a submodule and edited our CMakeList.txt. We managed to install our libraries and created our first web server. I scaffolded XNode, that is the system that handles the connections and implemented the first class and functions. I made the documentation and created examples functions/endpoints to help the other member of the Networking team. 

Next week, I will be working on the algorithm of XCoin which will illustrate the flow of actions, data, etc. with connected blocks such that it helps everyone to know where we are heading to and to pick a task. I will also implement the WebSocket controller.

@Mamoune Mouchtaki 

- This week:

We organized a meeting with all the currency team to see what do we have to do. This meeting leads us to split our team in order to work in other groups. 

After that I worked on the naivecoin tutorial. 

- Next week:

@Malo 

This week:

I implemented the ECDSA public private key generator using openSSL library. We chose this algorithm rather than RSA because it is way more secured. even though the code quantity is rather low, I had to read documentation to understand how this method works and why it is better than RSA. Then I had to learn how to implement it open SSL library, using a section on elliptical curves ([https://wiki.openssl.org/index.php/Elliptic_Curve_Cryptography](https://wiki.openssl.org/index.php/Elliptic_Curve_Cryptography)).

Newt week

Depending on the rest of the team, I will either make an implementation of the signature of work for the security team by building a sandbox.

@Lio 

@Picha 

**This week:**

We organised a meeting with the currency team in order to see what we could do in the project. We realized that at the moment it kind of overlap with the blockchain work. So we decided to split the currency team, and I joined the Front-end team.

In order to catch up what Front-end members have already done, I watched a video that explain how to use the Qt Library and coded some draft for our project.

**Next week:** 

Meeting with the other members in order to advance in the project. Make a draft by myself of the front page.

@Tim Valencony 

This week:

Worked by myself on the HomePage design while watching tutorials in order to better understand Qt. Was available to make the pushbuttons connect to a function that changed the page in the menu, just need to add some design to it now. Helped set up the skeleton of our ui and also started working on the login pop up, set up the frontend of it just need the backhand to work (make an sql database of the user info, make it more secure...etc). 

Next week:

I will continue my work on the login page, as well as work on my dedicated window of the project (design and functionalities).

@Laura Galindo 

During the team meeting on Monday, we split the work between the members of the Security team: nothing-at-stake (Salma), sand-boxing in C++ (Malo), and long-range attack (me). 

Throughout this week I did some more in depth research on how blockchains and Proof-of-Stake (PoS) work, to better understand how they can be attacked. I then focused on the long-range attack, investigating some existing countermeasures (the main one being *checkpoints*).

Next week I hope to speed up my work: try to fully understand a research paper which seems very promising, and start implementing it if it is appropriate, or else quickly find another solution to start coding as soon as possible !

@Clara  

This week I started working towards implementing a /blocks endpoint for the API to access the blockchain's block.

I made some research on endpoints and spent some time understanding how they work. I then read the documentation for drogon, the library we will use for Networking and WebSockets. I worked on learning how to use it for building controllers.

Next week I will start implementing WebSockets controllers for the endpoint.

@salma zainana 

This week I was more focused on studying the nothing at stake problem and to read about some already given solutions such as the slasher's algorithm. I got to see some already existing codes that solves this purpose and try to understand them. 

Next week I am planning to start implementing the slasher's algorithm( if Cyrus thinks it is good) and find more solutions. 

@Alex 

Front-end team experimented the Qt UI library, now ready to make the skeleton of the app with the main buttons. I was more focused on the styling and how we can make the app pleasant to see with style elements of the library

Next week: start coding the app with everyone (we just need to put everything "in common").

@Jean-Sebastien G. 

This week I helped with the implementation of the transaction part of the blockchain. 

Looked into a more elaborate, safe and energy efficient blockchain. Based off the example of "Decentralized Finance" and more precisely the "DFI" cryptocurrency. It mixes both the proof of work from the Bitcoin (since it is linked to Bitcoin), but it has itself a proof of stake.

Next week I will continue to work on the implementation of the blockchain and look into a way to link our blockchain (cryptocurrency) to a proof of work crypto (not necessarily Bitcoin).

@arthur 

I got familiar with the Qt library and started to create an 'test' app to test the different possibilities we have.  I understood how buttons, widgets and more can be used and designed.

Next week we will put all in common with the other members of the Front-End team and start coding the app. 

@Thang Long VU 

- Achieved in this week (week 2)
    - Set up the project and install dependencies ([https://www.notion.so/bx23/Getting-started-95430ee8cb7045efba0e0a30cd282b4e](https://www.notion.so/Getting-started-95430ee8cb7045efba0e0a30cd282b4e))
    - Read and understood more about the project.
    - Researched on Transactions part ([https://naivecoinstake.learn.uno/03-Transactions/](https://naivecoinstake.learn.uno/03-Transactions/))
    - Fixing some small bugs in the transaction code (https://github.com/BXPlus/XCoin/commit/f49a8f675fcb1c6d4fd1c0ec62585aef61af1156)
    - Adding Unspent transaction outputs (https://github.com/BXPlus/XCoin/commit/72e5458fd08ed5ef4a3654481d61971c93dca81d)
    - Adding Transaction signature (https://github.com/BXPlus/XCoin/commit/3163efad81cda61ccfdc3f762d3d728bce39d244)
    - Adding some Transaction validation (https://github.com/BXPlus/XCoin/commit/7160e3b804ec408438e671651b5f27bd1bfd549a)
- Plan for the next week (week 3)
    - Have a look at the Wallet part ([https://naivecoinstake.learn.uno/04-Wallet/](https://naivecoinstake.learn.uno/04-Wallet/))
    - Liaise with team members to finish the transaction code.

@Timothe 

This week we organised a meeting with the currency team where we decided to split and focus on other teams, projects. This led me to research ECDSA encryption for the transactions of the coins.

Next week I will go on the Task Market in order to find tasks to complete. Probably work to implement more things from the naivecoin tutorial.