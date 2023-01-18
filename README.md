## 🛠 Producer Consumer Problem

With the presence of more than one process and limited resources in the system the synchronization problem arises. If one resource is shared between more than one process at the same time then it can lead to data inconsistency.

Producer-Consumer problem is a classical synchronization problem in the operating system.

- **Producer** is a process which is able to produce data/item.
- **Consumer** is a Process that is able to consume the data/item produced by the Producer.
- Both **Producer** and **Consumer** share a **Common Memory Buffer**. This buffer is a space of a certain size in the memory of the system which is used for storage. The producer produces the data into the buffer and the consumer consumes the data from the buffer.

### ❌Problems

1. Producer should produce data only when the buffer is not full. In case it is found that the buffer is full, the producer is not allowed to store any data into the memory buffer.

2. Data can only be consumed by the consumer if and only if the memory buffer is not empty. In case it is found that the buffer is empty, the consumer is not allowed to use any data from the memory buffer.

3. Accessing memory buffer should not be allowed to producer and consumer at the same time.

For consistent data synchronization between Producer and Consumer, the above problems should be resolved.

### 🤔Solution

The general idea for solving this is that, the producer is to either go to sleep or discard data if the buffer is full. The next time the consumer removes an item from the buffer, it notifies the producer, who starts to fill the buffer again.

In the same manner, the consumer can go to sleep if it finds the buffer to be empty. The next time the producer puts data into the buffer, it wakes up the sleeping consumer.

<p align=center>
    <img src="https://user-images.githubusercontent.com/112488677/213111378-7ba1adf0-4878-4f78-ac94-1ede3040b652.jpg">
</p>

We will achieve this using **Semaphores** and **Mutex** locks.

### ▶ How to Run???

1. Execute the Command:
    ```shell
    sudo make
    ```
2. The output file object takes 3 arguments. Arguments in order:
    
    - **prds** - number of producers
    - **cons** - number of consumers
    - **runTime** - run time of the program

    <br>

    ```shell
    ./main prds cons runTime
    ```
