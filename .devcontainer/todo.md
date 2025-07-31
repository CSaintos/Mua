ToDo:
- NumberUtils should be a Number class that is its own library.
- Implement Result-Error handling for all classes which need it - to reduce repetition of if and return statements, its sugested to create a "checkError" function in the main class which throws exceptions when the underlying parameter has an Error-Result, then in the main loop, to catch those exceptions. FYI Exceptions can only "bubble up" one call stack at a time.
  - Separate console output use from the busineess logic.
- We can still further decouple the project (probably need to do some research on Dependency Inversion)
- The client is spitting back more output each time we give an input. Most probable cause is that the backend (Mua) is saving the input (need to remove that).
