5G integration/staging tree
===========================


What is 5G?
----------------

5G is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. 5G uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. 5G is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the 5G software, see https://5gcore.org/en/download/, or read the
[original whitepaper](https://5gcore.org/5g.pdf).


Building 5G
----------------

### Static compile

    git clone https://github.com/5G-Cash/5G
    cd 5G/depends
    make HOST=x86_64-linux-gnu
    cd ..
    ./autogen.sh
    ./configure --prefix=`pwd`/depends/x86_64-linux-gnu
    make


### Shared binary

    git clone https://github.com/5G-Cash/5G
    cd 5G
    ./autogen.sh
    ./configure
    make
