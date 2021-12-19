# Week 7: 13th to 19th of December

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
