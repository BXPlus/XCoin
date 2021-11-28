# Week 3: 15th to 21st of November

@Tim Valencony 

This week:

Made the final changes on the login pop up, there obviously is a bit of redesign to be done, but the main function of the pop up is now ensured, I just need to implement the connection between the function that the API team is going to give me (to verify which private key can be allowed to enter) and the actual fact that a user enters the application. Also started the design of the settings page, I drew the layout on paper and put every layout/widget needed in the code, just need a bit of styling now as well as some backend code to better link the information of the user with what is displayed on the page.

In terms of github, I replied to several questions from members of the team and helped them solve issues they had. I also helped the front end team create every branch so that everyone can separate on different tasks, and will handle the merging/conflict management once everyone is done. 

Next week:

I will continue working on the settings page and try to solve the issues I am currently having with implementing it and it actually showing in the mainwindow. I will also continue helping people with issues on git. Otherwise, I will probably find some new things to do, but that will be explained in next week's report. 

@Lio 

**This week:**

- I searched for different peer discovery libraries for our cryptocurrency
- However: failure to find a perfect one...
- Difficulty encountered: in understanding the libraries code as the use of other external networking library is everywhere. However, in order to be able to make our own algorithm → find the logic behind the peer discovery libraries we found. Continue on this matter next week.

**Next week:**

- I will start to write a general (not local) peer discovery algorithm, with the rest of the API team.

@Picha :

This week:

I started to get used to the tools to create a web page on QT. I am in charge of creating the payment and purchase pages for XCoin. We want to be able to make a page to buy XCoin and a page to pay between individuals or companies. I drew a first model of what I want to do for my web page.

Next week:

I'd like to finish the design of the webpage in order to connect data created by the other teams on my page.

@Alex 

This week:

With the frontend team, we decided more or less what we wanted as a global theme (colours, widget layouts, etc). I started working on the global styling and small details that are specific to Qt Design. I also worked on the home page, which welcomes the user and is the first page once the user is logged in. It displays the overview of the other most important pages in smaller widgets, so it's pretty complicated to layout the widgets correctly. It is also a challenge to work without the API functions since these will change most of what we are doing right now (not only in terms of design, but also in terms of layout). Therefore, the most we can do right now is display some titles and "theoretical" layouts. 

Next week:

I will start working on the contacts page (list of users to which one can pay/send coins). I will possibly try to find a way to make custom widgets for some things that don't appear very good in Qt. For example, the scroll bar doesn't look good, so I will try to design a custom scroll bar. 

@arthur 

This week : 

First, with the front end team, we decided on which page each member is going to work on and discussed the designs we would like for these pages. I am in charge of the Balance page which is suppose to show the user the amount of money (XCoin) he has, and the history of his previous transactions. I started to work on this page, but we have to wait for functions from other teams to go deeper in the implementations of the pages.

Next week : 

I will continue to work on this page and add more details to make the page look better and connect it to the data from the other teams if possible. 

@Mamoune Mouchtaki 

This week:

I started working with the front end team on the pages of the app. I first started by getting used to the Qt library by watching some videos. Then I coded a graph with a zoom in/ zoom out options. 

Next week:

I will finish my code then I will discuss with the other member of the front end team to work on something else.

@Clara  

This week:

Learned how to use the drogon library to create an XNode controller through an endpoint that returns a JSON response. Implemented a /blocks endpoint to list the blockchain's block. This endpoint should give us access to the resources of the blockchain. Also did some research on P2P discovery, and looked at some libraries for this.

Next week:

With the API team we will look at finding and implementing an algorithm for the peer discovery.

@salma zainana 

During the first part of this code i spent time trying to understand how does casper proof of stake algorithm work and trying to implement it. At the end i stopped doing this since it s not needed anymore. Instead i got another task : implementing a code to encrypt and decrypt messages. I got to use the library openssl which provides functions for performing symmetric encryption and decryption operations and i commited my code but still it needs some modifications and "retouche"

For next week, i need to discuss with youssef what i need exactly to do for the nothing at stake problem , to finish my code concerning EVP . i also need to write a code that writes from a file and can read from a file .

@Laura Galindo 

This week:

I finished my searches on long-range attacks, distinguising 3 different types of long-range attacks, and investigating all the main countermeasures existing, making a concise summary. I was however unable to yet find a way to implement them concretely, as I must first discuss with my collegues on how they implemented blockchains in C++.

Next week:

I will start implementing the solutions to long-range attacks (I'm aiming for timestamping, checkpoints and longest-chain rule at least).

@Cyrus Pellet 

This week I expanded upon the encoding/decoding class to ensure a full blockchain could be transmitted with minimal size and overhead. I also added more protobuf message definitions for blockchain synchronisation transactions between nodes.

Next week I will keep on expand this and test out the blockchain synchronisation in real life with two nodes on the network.

@Kevin Messali 

This week I have implemented the WebSocket Controllers and given examples of how to use them, and create routes. I have read an article on how the block chain synchronization and peer-discovery are implemented in Bitcoin, with the DNS Seeder and Header-First sync. 

Next week, I will start building our own DNS Seeder and implement the Header-First sync.

@Timothe 

This week I started to do research on the wallet part of the coin and did some programming in the project. Next week I will continue what I have started and expand on it further.

@Malo 

This week I added the functions getPriv() and getPub() to Keys, and I understood the peer discovery principle and looked for a library for our system, unfortunately none of us did find one, so next week I will start (and finish) a peer discovery algorithm. I will also add new functions to Keys: keyFromPrivate(), keyFromPublic() and verify().

@Thang Long VU 

- Achieved in this week (week 3)
    - Almost done with the Transaction part, only requires Keys-class specific functions from XNode
    - Discussed with team member and changed the design txIns and txOuts in the transaction class from arrays to vectors (https://github.com/BXPlus/XCoin/commit/325025f19356768f31994f812b044d0235778713)
    - Added validate Transaction (https://github.com/BXPlus/XCoin/commit/55c4bd671027249177b8b2afba57d11c883a77a7)
    - Fixed isValidTxOutStructure method (https://github.com/BXPlus/XCoin/commit/202bd6dddc4e40e57219453e46143544100b95f2)
    - Added isValidAddress method (https://github.com/BXPlus/XCoin/commit/3fe034bcd5f22c9b5e671716a6f4dcacf84b5a5d)
    - Added the amount of coinbase output, the validation of coinbase transaction and getCoinbaseTransaction (https://github.com/BXPlus/XCoin/commit/2adc2747d971f1016e9ce829b48383418a16cfa9)
    - Implemented signTxIn (creating signature) and validateTxIn (https://github.com/BXPlus/XCoin/commit/8b05a49cd6912a1c909391062b5f01fea8a70723)
- Plan for the next week (week 4)
    - Continue research on Wallet part ([https://naivecoinstake.learn.uno/04-Wallet/](https://naivecoinstake.learn.uno/04-Wallet/))
    - Write unit tests for the Transaction part
