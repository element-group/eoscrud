#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

using namespace eosio;

using std::string;

class eoscrud : public eosio::contract {
  public:
    using contract::contract;

        /// @abi action
        void create( uint64_t id, account_name user, string data ) {
            records recordstable( _self, id );
            auto existing = recordstable.find( id );
            eosio_assert( existing == recordstable.end(), "record with that ID already exists" );
            eosio_assert( data.size() <= 256, "data has more than 256 bytes" );

            recordstable.emplace( _self, [&]( auto& s ) {
               s.id         = id;
               s.owner      = user;
               s.data       = data;
            });

            print( "Hello, ", name{user} );
            print( "Created with data: ", data );
        }

        /// @abi action
        void read( uint64_t id ) {
            records recordstable( _self, id );
            auto existing = recordstable.find( id );
            eosio_assert( existing != recordstable.end(), "record with that ID does not exist" );
            const auto& st = *existing;
            print("Data: ", st.data);
        }

        /// @abi action
        void update( uint64_t id, string data ) {
            records recordstable( _self, id );
            auto existing = recordstable.find( id );
            eosio_assert( existing != recordstable.end(), "record with that ID does not exist" );
            const auto& st = *existing;

            recordstable.modify( st, 0, [&]( auto& s ) {
               s.data = data;
            });

            print("Data: ", data);
        }

        /// @abi action
        void destroy( uint64_t id ) {
            records recordstable( _self, id );
            auto existing = recordstable.find( id );
            eosio_assert( existing != recordstable.end(), "record with that ID does not exist" );
            const auto& st = *existing;

            recordstable.erase( st );

            print("Record Destroyed: ", id);

        }

  private:
    /// @abi table
    struct record {
       uint64_t        id;
       account_name    owner;
       string          data;
       uint64_t primary_key()const { return id; }
    };

    typedef eosio::multi_index<N(records), record> records;
 };


EOSIO_ABI( eoscrud, (create)(read)(update)(destroy) )