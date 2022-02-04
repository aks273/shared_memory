# Semaphore

A semaphore is a synchronisation primitive, as is a mutex lock.

A semaphore is an unsigned int, with atomic operations. I.e. multiple 
operations cannot interupt each other.

We interact with a semaphore using `wait()` or `post()`. Both operations are 
atomic:
- wait 
    - tries to decrement the value. If it is greater than 0, it does this 
    straight away and returns.
    - if it is zero, it waits until the value is greater than zero.
- post
  - increments the value and returns

## Uses:
### Binary semaphore
similar to a mutex lock
  
- initialise a semaphore to 1, call wait() when we want to access the
shared resource/code. Call post() when we want to release
- not the best, because there is no concept of ownership, any process 
can call post() even if another has called wait()
- probably shouldn't use if a mutex lock also works.
