# EOS Contract - CRUD Example
This is a very minimal example of an EOS Smart Contract that will do 4 simple things. Create, Read, Update, and Destroy. 
This contract is basically a simple database without any great features. Each "record" includes an `id`, `user`, and `data` which is a string. 

### Setup
This step requires you to have a EOS blockchain server already setup and running. You can follow the [Tutorial](https://github.com/EOSIO/eos/wiki/Local-Environment#building-eosio) to get up and running. 
```
// run the EOS server with --contracts-console
nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console
```
Then clone this repo.
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
cleos create account eosio eoscrud <EOS address here> 
cleos set contract eoscrud ../eoscrud -p eoscrud
```

## Contract Interaction
While interacting with the contract, you'll see the `print` logs inside the EOS server console.


### Create (id, user, data)
```
cleos push action eoscrud create '[1, "user", "oh heyyy this is new"]' -p eoscrud

// [(eoscrud,create)->eoscrud]: CONSOLE OUTPUT BEGIN =====================
// Hello, userCreated with data: oh heyyy this is new
// [(eoscrud,create)->eoscrud]: CONSOLE OUTPUT END   =====================
```

### Read (id)
```
cleos push action eoscrud read '[1]' -p eoscrud

// [(eoscrud,read)->eoscrud]: CONSOLE OUTPUT BEGIN =====================
// Data: oh heyyy this is new
// [(eoscrud,read)->eoscrud]: CONSOLE OUTPUT END   =====================
```

### Update (id, data)
```
cleos push action eoscrud update '[1, "this is updated"]' -p eoscrud

// [(eoscrud,update)->eoscrud]: CONSOLE OUTPUT BEGIN =====================
// Data: this is updated
// [(eoscrud,update)->eoscrud]: CONSOLE OUTPUT END   =====================
```

### Destroy (id)
```
cleos push action eoscrud destroy '[1]' -p eoscrud

// [(eoscrud,destroy)->eoscrud]: CONSOLE OUTPUT BEGIN =====================
// Record Destroyed: 1
// [(eoscrud,destroy)->eoscrud]: CONSOLE OUTPUT END   =====================
```

