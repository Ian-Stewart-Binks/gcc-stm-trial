== GCC STM Trial

GCC offers [STM support](https://gcc.gnu.org/wiki/TransactionalMemory). This repository plays with the STM support by benchmarking a linked list implementation against a traditional lock based implementation.

To run the STM implementation of the linked list, run
```
gcc -Wall -fgnu-tm -o tx_linked_list tx_linked_list.c
```
