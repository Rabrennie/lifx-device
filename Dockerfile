FROM ubuntu

# install basic stuff
RUN apt-get update && apt-get install -y \
g++ \
make \
cmake

# install g{test,mock} sources & put headers into /usr/include
RUN apt-get update && apt-get install -y \
google-mock \
libgtest-dev

# build & install gtest (cmake -DBUILD_SHARED_LIBS=ON . for shlibs)
RUN cd /usr/src/gtest ; cmake . ; make
RUN mv /usr/src/gtest/*.a /usr/lib/

# build & install gmock (cmake -DBUILD_SHARED_LIBS=ON . for shlibs)
RUN cd /usr/src/gmock ; cmake . ; make
RUN mv /usr/src/gmock/*.a /usr/lib/
