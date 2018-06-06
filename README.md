# EOS Contract - CRUD Example
This is a very minimal example of an EOS Smart Contract that will do 4 simple things. Create, Read, Update, and Destroy. 
This contract is basically a simple database without any great features. Each "record" includes an `id`, `user`, and `data` which is a string. 

### Setup
```
git clone https://github.com/element-group/eoscrud
cd eoscrud
```

### Build Contract
```
eosiocpp -o eoscrud.wast eoscrud.cpp
eosiocpp -g eoscrud.abi eoscrud.cpp
```

### Deploy Contract
```
cleos create account eosio eoscrud.code <EOS address here> 
cleos set contract eoscrud.code ../eoscrud -p eoscrud.code
```

### Contract Interaction
While interacting with the contract, you'll see the `print` logs inside the EOS server console.
```
cleos push action eoscrud.code create '[1, "user", "oh heyyy this is new"]' -p user
cleos push action eoscrud.code read '[1]' -p user
cleos push action eoscrud.code update '[1, "this is updated"]' -p user
cleos push action eoscrud.code destroy '[1]' -p user
```

