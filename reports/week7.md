# Week 7: 13th to 19th of December
@Tim

This week:

- I finished some last touches on the Settings page
- This week was mostly github related, as I helped several people from the frontend team with GitHub, by resolving conflicts for them and merging their branches
- Also github related, I with the help of Cyrus and Kevin, merged all of the frontend work into the main branch so that everyone can run it on CLion (we don't work on QT anymore), it was runnable until new commits were posted, now I am having errors not related to frontend. Therefore, next week I will try to make it runable on CLion again by creating a new branch so that we get back the changes that were made when it was runable on CLion, and will merge everything at the end to facilitate the task.


@Alex 

This week:

- Change of plans with respect to last week's goals: the styling and theme-change options were done by Clara and Tim.
- I changed the functioning of the contact payment page. Instead of clicking on the pay button to open the pay dialog, you can now click on the contact's entire row. It is more user-friendly and aesthetically pleasing.
- Merged the payment page and contacts page together since they were pretty similar → app is more compact now
- Changed the style of the search buttons

@Laura Galindo 

Right now, the nodes are not authentified: there is no way to know a peer is legit. Therefore, we wish to send a token along every request to give us a way to verify that the person making a request is running a genuine node. So this week, I wrote the functions `generate` and `check` in `XNode/node.cpp` to create and check tokens sent and received from a specific peer. I used JSON Web Tokens (JWT) as it is a common method, and for this I used the library `jwt-cpp`, as it is quite hard and takes a lot of time for a beginner to implement from scratch.

I also ran Cppcheck across all the project folders to check the validity of our files’ code, and contacted my collegues who wrote code where there were issues, so that they could make corrections.

Next week I will try to integrate the tokens into gRPC, which is a specialised protocol used by nodes on the XCoin network to communicate.

@Lio 

This week:

- Implemented a [struct](https://www.cplusplus.com/doc/tutorial/structures/) called `XNodeSettings` that contain all the Node's settings.
- created a function `loadNodeSettings()`
- created a function `newSettings`

Next week:

- Should the implementation  during the holidays

@Youssef Chaabouni 

This week:

• Fixed some errors with the wallet file

• Did some further documentation about proof of stake

Next week:

• Make sure everything is done and works concerning the proof of stake

@Clara  

This week, I worked on the styling and theme-change options (we implemented a “light mode”). In particular, I worked on the design and aesthetic of the contacts page, that is now merged with the payment page. I also worked on the “Balance page”.

@Kevin Messali 

This week:

 I fixed with @Cyrus Pellet some issues we were facing with the blockchain sync and the UI. We merged the frontend branch into the master and provided the fixes needed. We added QT libraries in our CMake so we can run the whole project at once. We also continued working on the interface of the network part with the UI. I also provided help for the UI team and helped creating the Tricount class for @Picha.

Next week:

I will continuing working on the interface with the network part and the UI and fixing the issues.

@Picha

This week, I finished my assigned job on Front-End. I started the Tricount algorithm. 
