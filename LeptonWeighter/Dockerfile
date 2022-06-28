ARG VERSION=20.04

FROM ubuntu:${VERSION}

# Stop installer from showing interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Get dependencies
RUN apt update && apt install -y \
    git gsl-bin libgsl-dev hdf5-tools \
    libhdf5-dev python3 g++ pkg-config \
    make cmake libcfitsio-bin libcfitsio-dev \
    python3-fitsio libsuitesparse-dev \
    libboost1.67-all-dev libopenblas-base \
    libpython3-all-dev libopenblas-dev pip 
# Create a folder inside the home directory
RUN mkdir -p /home/ubuntu/programs

ENV MAINDIR=/home/ubuntu/programs

ENV SQUIDSDIR=${MAINDIR}/SQuIDS
ENV SQUIDSVERSION=v1.3.0

ENV NUSQUIDSDIR=${MAINDIR}/nuSQuIDS
ENV NUSQUIDSVERSION=1.11

ENV PHOTOSPLINEDIR=${MAINDIR}/photospline
ENV PHOTOSPLINEVERSION=v2.1.0

ENV LEPTONWEIGHTERDIR=${MAINDIR}/LeptonWeighter

ENV LEPTONINJECTORDIR=${MAINDIR}/LeptonInjector


# Install SQuIDS
WORKDIR ${MAINDIR}
RUN git clone https://github.com/jsalvado/SQuIDS.git
WORKDIR ${SQUIDSDIR}
RUN git checkout tags/${SQUIDSVERSION} -b ${SQUIDSVERSION}-branch
RUN ./configure && make && make install

# Install nuSQuIDS
WORKDIR ${MAINDIR}
RUN git clone https://github.com/arguelles/nuSQuIDS.git
WORKDIR ${NUSQUIDSDIR}
RUN git checkout tags/${NUSQUIDSVERSION} -b ${NUSQUIDSVERSION}-branch
RUN ./configure && make && make install

# Install photospline
WORKDIR ${MAINDIR}
RUN git clone https://github.com/icecube/photospline.git
WORKDIR ${PHOTOSPLINEDIR}
RUN git checkout tags/${PHOTOSPLINEVERSION} -b ${PHOTOSPLINEVERSION}-branch
RUN cmake . -DCMAKE_INSTALL_PREFIX=/usr/local && make install

# Install LeptonWeighter
WORKDIR ${MAINDIR}
COPY source ${LEPTONWEIGHTERDIR}
WORKDIR ${LEPTONWEIGHTERDIR}
RUN ./configure && make && make install && make python-install
RUN pip3 install tables

# Install LeptonInjector
WORKDIR ${LEPTONINJECTORDIR}
RUN git clone https://github.com/icecube/LeptonInjector.git source
RUN mkdir build && cd build && cmake ../source && make && make install

# Set up paths
RUN echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lib:/usr/lib:/usr/local/lib" >> ~/.bashrc
RUN echo "export EARTH_PARAMS=${LEPTONINJECTORDIR}/source/resources/earthparams" >> ~/.bashrc
RUN echo "export PYTHONPATH=$PYTHONPATH:/usr/local/lib/python3/dist-packages/" >> ~/.bashrc

WORKDIR ${LEPTONINJECTORDIR}/source/resources/examples