# SNHU Cross-Course Portfolio
### Author: Kyle Keiper

In short, this repository is a collection of work from various SNHU courses that I need to put together for the final program project. You will find a collection of various documents and programs that I have compiled in this repository.

## CS 370 - Current/Emerging Trends in CS

IN CS-370, we learned about the growing trend towards Artificial Intelligence through Machine Learning. The main areas of interest were Neural Networks and Deep Q-Learning. Our final project was to implement a Deep Q-Learning algorithm to aid an AI agent, a Pirate, in winning a treasure hunt. We were given all code except for the algorithm itself. 

* **What do computer scientists do and why does it matter?**

Computer scientists use the mathematical power provided by computers to investigate the world. We gain knowledge that would otherwise be very unwieldy to calculate. The topic studied in this class, Artificial Intelligence, will help scientists by possibly discovering information in a way that they may not have recognized before.

* **How do I approach a problem as a computer scientist?**

As a Computer Scientist, I approach problems by considering what "grunt work" the computer could do for me, but I don't mean grunt work in the idea of "something I could do myself but can't be bothered with". In this context, I mean the nitty-gritty that I myself may very well not understand how to do, and need AI or simple mathematical models to explain the conclusions reached. 

* **What are my ethical responsibilities to the end user and the organization?**

My ethical responsibilities include making sure that AI is used responsibly. It would be very unethical to use it to generate data that is incorrect, or to create pieces of content that invade privacy, or use it to attempt to hack companies maliciously. I must make sure that any usage of AI is properly vetted and, while it may not be fully understood, at least make sure we have a clear idea of what the AI is going to attempt to do before turning it on. Also, it is our responsibility to make sure there are safeguards in place to prevent usage that violates ethical principles.

## CS 340 - Client/Server Development

* **How do you write programs that are maintainable, readable, and adaptable? Especially consider your work on the CRUD Python module from Project One, which you used to connect the dashboard widgets to the database in Project Two. What were the advantages of working in this way? How else could you use this CRUD Python module in the future?**

One of the big ways to write maintainable software is to use dependency injection; in the AnimalShelter.py file, we use it to be able to "inject" the username and password into the class, that way we can load the credentials from where-ever they live, such as an .env file or shell built-ins.

Another way is to abstract the actions a class can take, which we did with our CRUD methods. We don't necessarily care *how* the animals are created, just that they *are* created; it's the same with Reading, Updating and Deleting. As long as the data gets saved, we can simply concern ourselves with the business logic of the project, not the actual implementation details.

* **How do you approach a problem as a computer scientist? Consider how you approached the database or dashboard requirements that Grazioso Salvare requested. How did your approach to this project differ from previous assignments in other courses? What techniques or strategies would you use in the future to create databases to meet other client requests?**

I've been working in software for long enough that I don't really think my approach to grazioso salvare was different than any of my previous ones. I'm used to developing CRUD apis for the work I do. I've worked on budgeting software for myself, gardening calendar stuff, and student information for work, and I have frequently created apis that are based in CRUD.

Techniques and strategies that I would use are to draw up the information required in a datatype; for example, when developing a dashboard for tracking expenses and income, my thoughts would be "The bubble of data I want is a Transaction, so what information exists in a transaction? A credit/debit type, an amount type, a category type, a datetime type, etc". Then I would create the database for it. With MongoDB, however, I wouldn't need to define the schema. 

* **What do computer scientists do, and why does it matter? How would your work on this type of project help a company, like Grazioso Salvare, to do their work better?**

Computer scientists find efficient ways to model and solve real-world problems using digital tools. For Grazioso Salvare, I imagine they keep track of all their potential dogs in a spreadsheet, if they're tech-savvy, or a binder if they're not. Even just having a map of where each available dog is located would be nearly impossible using a binder, and would go out of sync very quickly. By using computer science to move the information to a digital catalogue, we can enable always-in-sync mapping and data aggregation from the data available to the company. This is much more difficult to do with even spreadsheets, let alone paper binders.

## CS 330 Computer Graphics

When I design software, I like to sit down and think about abstractions. In the case of Graphics Programming, what happens if you want to use the same 
geometry in different places in the window? Reprogramming all the vertices is really cumbersome, so I like using a solution of Mesh+Model, when one Mesh 
can be used by multiple Models placed throughout the scene. 

When I develop software, I like to have documentation up on one monitor, while having the IDE open in the other. In this situation, it was using learnopengl.com as the documentation and CLion as the IDE. I also liked to start a new module by cloning the previous project, that way I didn't have to rewrite all the utility classes, like Mesh, Model, Shader, or Timer. One new strategy I used was to incorporate Blender, a 3D Modeling Software, into my workflow. I've never sat down to really learn Blender, but because I had to model non-trivial objects, I didn't want to enter numbers by hand.

Lastly, computer science helps me reach my goals because computer can operate so much faster than I can. They can take abstract math that I cannot visualize, and then plot it out in a way that makes sense to my monkey brain. A list of numbers doesn't mean much to me, but when they're rendered out in 3d space as a model, I can visually recognize what the numbers are supposed to represent. This helps me to be able to design something before fabricating it.

[Design Decisions](https://github.com/kkeiper1103/snhu-portfolio/blob/main/Module%202_%20Project%20Proposal.docx)

## CS 320 Software Test Automation

* **How can I ensure that my code, program, or software is functional and secure?**

    By creating automated test suites that are ran by automation agents, like Jenkins, we can ensure that functionality is not accidentally removed, or bugs accidentally created. Tests allow us to objectively measure how well our code meets business requirements, as well as objectively know how much of the code has been covered for errors.
* **How do I interpret user needs and incorporate them into a program?**

    By listening and probing clients for what they'd like, I write tests to make sure the features are incorporated. For example, if a system needs IDs, they probably need to be unique, so we would write a test to make sure two objects in the same system cannot share an identical ID. Test automation allows us to know if client needs are taken into account on each iteration of software release.
* **How do I approach designing software?**

    Personally, I like to conceptualize the software, then skeleton it. At that point, I begin writing tests to start incorporating features. When all the requirements have a related test, and each test passes, I consider the software feature complete, although it may not be content complete.
## CS 255 System Analysis and Design

[Business Requirements](https://github.com/kkeiper1103/snhu-portfolio/blob/main/CS%20255%20Business%20Requirements%20Document%20Template%20(kkeiper1103).docx)

[System Design](https://github.com/kkeiper1103/snhu-portfolio/blob/main/Project%202_%20System%20Design%20Document%20-%20kkeiper1103.docx)

* **Briefly summarize the DriverPass project. Who was the client? What type of system did they want you to design?
What did you do particularly well?**

    The DriverPass project was a software project designed to help Liam create a business that trains students to pass drivers' exams. They needed a web application that allowed for multi-user management, client billing, and fetching of remote data. I think I did a good job of capturing the class diagram of the project.
* **If you could choose one part of your work on these documents to revise, what would you pick? How would you improve it?**

    I would improve the use-case diagram. I did this wrong the first time and I would revise it to make it more like what it's supposed to be.
* **How did you interpret the user’s needs and implement them into your system design? Why is it so important to consider the user’s needs when designing?**

    I listened and used my experience to create what they wanted, even if they said it wrong or forgot features that are needed. The user is paying the developer; if the project doesn't come out as a useful tool for the user, they won't hire your company again. The client is always "right", even when they aren't.
* **How do you approach designing software? What techniques or strategies would you use in the future to analyze and design a system?**

    I like to start by imagining the system, then create UML class diagrams. I feel like knowing what parts have which responsibilities helps us know how the system interacts and where it can be improved.

## CS 250 [Sprint Review and Retrospective](https://github.com/kkeiper1103/snhu-portfolio/blob/main/Journal%20-%20Scrum%20Master.docx)
* **How do I interpret user needs and implement them into a program? How does creating “user stories” help with this?**
 "User stories" are a great way to gather boiled down reasons for a feature. It helps aim the direction of a project by giving a "_who_ needs _what_ because _why_". 
* **How do I approach developing programs? What agile processes do I hope to incorporate into my future development work?**
  I already incorporated a lot of agile processes in my development. I regularly communicate with the client to see if the direction I'm trending toward is the direction they're envisioning. I like the idea of small increments that are regularly tested and reviewed, so I'm definitely adopting this practice.
* **What does it mean to be a good team member in software development?**
  In software development, a good team member means doing what I can, when I can, and staying out of things that aren't mine to handle. Agile emphasizes that all developers share the _same_ title, so not having a chip on my shoulder for the type of development I do, whatever that is, is very important. No one member is more important than another, so remembering that might be the best thing I can do.
