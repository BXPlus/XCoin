# Week 6: 6th to 12th of December

@Alex

This week: 

- With the Qt default scrollbars not being very good-looking, I tried to recreate the macOS scrollbar with style elements as most as possible. In the end the result is quite satisfying.
- Corrected the contact page mistake. Now it is functional, you can scroll with as many contacts as needed.
- Developed "add contact" button with Tim in contacts page: consists in entering a public key or address and keeping it in one's registered contacts
- Unfortunately, I spent most of the week (5 days) trying to merge and run the project on my laptop.
    - Further explanation: since the beginning of the project, I was working with Qt 6.2.2, while the others worked with version 5.12.5. As such, they used some Qt library functions that couldn't work on my side. Until now, these were manageable without changing version because the functions that differed were directly "translatable" or replaceable. However, when we merged on Monday there were some files that I couldn't avoid using, that were blocking compilation on my side. Therefore, I tried to change Qt version, but for some reason, and even after carefully changing the kits, version, re-downloading Qt, re-downloading Qt Creator, recloning the project, starting everything over, there was a constant error message saying that Qt couldn't find the target to the makefiles. After attempting different approaches for 5 days, I finally managed to get a working version thanks to the help of @Tim Valencony and @Kevin Messali. This is definitely an example of a challenge of working in a big team, so, lesson learned: make sure to have the same exact environment before starting the project.
- During the week-end I developed the payment page, which allows to pay someone "in XCoins". This includes a dynamic contact search bar, a dialog that allows the user to input digits to indicate how much coins he wants to transfer.

Next week:

- I will perfect Tim's work on the contact page, and add style on most other pages.
- I will try to set the function of the setting button "change theme" to switch between dark and light themes. This is not trivial since it's not possible to change the stylesheet file used from just a button toggle, so it requires manipulating parent and child widgets...

@Tim

This week:
- I perfected the original work on the contact page made by Alex, as he was unable to work for about four days straight on the project due to an issue. Thus, I created the addcontact Dialog and made it functionnal. I also made it possible to edit the contact list and remove contacts from the scroll bar. 
- I helped a lot with github this week, as I merged and handled the conflicts of most of the UI team's members code. I also helped set up the environment for Clara so that she could have something to work on. Finally, I helped merge the whole code from the frontend to the master branch, so that we can start connecting the backend with the UI work.
- Furthermore, I connected the dark/light mode toggle so that there is a change of style once it is pressed. I also finalized the style of the settings page.
- To finish, I implemented the balance page and set up the style as to have a tab widget which will come in handy moving forward in the project.

Next week:
- I will finish upgrading the settings page so that it is completely finished, meaning the user can edit the address and other arguments of the page.
- I will continue my role as github master.
- I will try and connect functions made from the API team and implement them with QT.

@Picha 

**This week:**

I finish all my assigned tasks :

- Create a QDialog page for the Payments page
- Finish the Payment page template
- Create a button to open the payment page
- Finish the template for the page to purchase XCoin

**Next week:**

I will try to fix the design issues of my page. I will also try to connect the line where the user inserts the amount of XCOIN they want with the line that summarizes their total amount before paying. I have to take into account the value of the currency as well.


@Lio

**This week:**  

- Studied the UI code that was just merged with the master branch
- Added two functions into `XNode/XNodeSDK.h`

**Next week:**

- Implement new properties & functions into `XNode/XNodeSDK.h`



@Laura Galindo 

This week I implemented the Moving Checkpoints countermeasure for long-range attacks. Unfortunately, for medical reasons, I was not able to go beyond.

So next week I will check the reasoning of my implementation, and then either implement another of the countermeasures, or write a simple and general mini-algorithm to flag "suspicious" transactions and then implement it.

@Thang Long VU 

This week:

- Fixed the issues with storing objects as keys of maps by changing map to set and write an operator< for class  (https://github.com/BXPlus/XCoin/commit/2212783c2023a26f28305e5022f79a80b3c6f19b, https://github.com/BXPlus/XCoin/commit/5647c3e36c2c732f932ebbfde4b3a5467912d201)
- Wrote unit tests for some functions:
    - Initialization of UnspentTxOut and TxOut (https://github.com/BXPlus/XCoin/commit/436df040e3d8c99e63bd649ffc793cb93987112f)
    - getTransactionId (https://github.com/BXPlus/XCoin/commit/7ed638a459f720b7771dba3140eac8045d661d31)
    - isValidAddress (https://github.com/BXPlus/XCoin/commit/8b9611ad588ae4e75cb9b9e9675b6fba81f044ac)
    - hasDuplicates (https://github.com/BXPlus/XCoin/commit/243589e64d49081c3274986685eeec0a2abcd777)
    - getCoinbaseTransaction (https://github.com/BXPlus/XCoin/commit/3c65db98c19feea91572969e5eed4a98683c1fe9)
    - findUnspentTxOut (https://github.com/BXPlus/XCoin/commit/3c2a7b20bb4b16b93066045f46a07d18f63eca9a)
    - validateCoinbaseTx (https://github.com/BXPlus/XCoin/commit/23d1af92a14c05e0feba1ae9678f14fa1aa9bc36)

Next week:

- Finish writing tests for transaction.cpp

@Youssef Chaabouni 

This week:

- Learned about Google tests
- Started implementing tests for the transaction functions

Next week:

- Fix some issues with the blockchain
- Add some missing unit tests for the blockchain
- Write unit tests for the staking process

@Kevin Messali 

This week: 

We have merged with @Cyrus Pellet the gRPC branch into the master branch, and we have finished a first case of blockchain synchronization. We tested it and managed to make it work with a 50 block synchronization. I have also fixed the function that lists the blockchain as a list of blocks.

Next week:

We will be finishing fully the synchronization with @Cyrus Pellet and more precisely I will be doing the header synchronization.

@Malo 

This week I plugged the functions I make in keys into Wallet and transaction and I tried to debug code from Long Vu in transaction. Next week I will probably make the contact storage.

@Clara 

This week, I started working on the main design of the app. In particular, I worked on making the app's design more coherent as a whole, and made sure that the configuration and code for styling was consistent between the pages "Contacts", "Balance", "Pay" and "Settings" . 

Next week, I plan on implementing a "theme-change" options, i.e when a button is clicked, the design of the app goes from "dark mode" to "light mode". This will probably involve implementing changes regarding the colors and overall appearance. 

@Timothe

This week I helped implement the tests for the transaction functions and made sure that everything was in order. I looked over the code from the front-end team and asked questions in order to understand what they wrote.
Next week I will go through more of their code to fully understand it. And look over what other people did so that I have a full overview of the project.
