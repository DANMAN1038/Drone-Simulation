Team 29, Danial Syed(syed0053), Taha Rao(rao00041), Bach Tran(tran1003), Ibrahim Hosh(hosh0013)

This project is a simulation of a drone delivery system with a rough replica of the University of Minnesota Twin Cities Campus.

How to run the simulation (overview of the whole project, not just the hw4)? //TODO

This is a full stack project that enables C++ code in the backend to receive input from our frontend which is made from a mix of HTML and Javascript. Users are able to add trips to the simulation using our frontend UI which will schedule a trip for a drone to take allowing the user to pick the path and travel method it takes. Users also have the ability to add humans whom can roam around freely, as well as speed up the simulation in the top left hand corner.

Feature 1: Displaying Notifications
    Displays notifications to the frontend UI on the left hand side to notify the user when a drone has started its delivery and when it has ended 
    This feature is significantly interesting since it updates the user with the status of the drone that was scheduled. Thus, there is no need to endlessly follow the drone and see where its current location is. Notifications can practically serve as checkpoints that allow the user to know how far the drone has gotten up until that point.
    This feature added onto the existing work by becoming more user friendly with regards to updating the user with the status of the drone. 
    We chose the observer design pattern as it allows our drone object to update and notify us with its current status. Another reason we chose this design pattern is because it was minimal and did not tamper too much with the already existing implementation of the project which lowers risk of error.
    Schedule a trip as you normally would and it will automatically send notifications to the front end UI on the left hand side of the simulation screen.

Feature 2: Data Collection //TODO
What does it do?
    This feature is signficantly interesitng as it allows users to observe 
How does it add to the existing work? 
Which design pattern did you choose to implement it and why? 
Instruction to use this new feature (if the new feature is not user interactable, please mention this as well)

Sprint retrospective
    What went well:
        Group was very well organized and it was clear everyone knew what we were working on
        Group communicated well to update others with current progress
    What went poor:
        More meetings could have been made to teach others of new findings
        Difficult to divide up work evenly with constant aid being needed (specifically with regards to the coding)
    What we would change:
        Have a proper timeline of when a task should be done
        Be more of an outlet for other team members to reach out to if stuck

Youtube Demo: //TODO

UML extension diagrams: //TODO