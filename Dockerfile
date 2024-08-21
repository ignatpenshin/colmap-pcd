FROM nvidia/cuda:12.2.2-devel-ubuntu22.04

ARG COLMAP_GIT_COMMIT=main
ARG CUDA_ARCHITECTURES=native
ENV QT_XCB_GL_INTEGRATION=xcb_egl

# Prevent stop building ubuntu at time zone selection.  
ENV DEBIAN_FRONTEND=noninteractive

# Prepare and empty machine for building.
RUN apt-get update && apt-get install -y \
    git \
    cmake \
    build-essential \
    libboost-program-options-dev \
    libboost-filesystem-dev \
    libboost-graph-dev \
    libboost-system-dev \
    libboost-test-dev \
    libeigen3-dev \
    libsuitesparse-dev \
    libfreeimage-dev \
    libmetis-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libglew-dev \
    qtbase5-dev \
    libqt5opengl5-dev \
    libcgal-dev \
    libcgal-qt5-dev \
    libatlas-base-dev \
    libsuitesparse-dev \
    libpcl-dev \
    libopencv-dev \
    sudo \
    wget

ARG USERNAME=user
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
RUN adduser user dialout

# Make bash history persistent
RUN SNIPPET="export PROMPT_COMMAND='history -a' && export HISTFILE=/commandhistory/.bash_history" \
    && mkdir /commandhistory \
    && touch /commandhistory/.bash_history \
    && chown -R $USERNAME /commandhistory \
    && echo "$SNIPPET" >> "/home/$USERNAME/.bashrc"

# Install ceres 2.1.0
WORKDIR /tmp
RUN wget -q http://ceres-solver.org/ceres-solver-2.1.0.tar.gz && \
  tar zxf ceres-solver-2.1.0.tar.gz && mkdir ceres-bin
WORKDIR /tmp/ceres-bin
RUN cmake /tmp/ceres-solver-2.1.0 && \
  make -j12 && \
  make install

# Build and install COLMAP.
WORKDIR /home/$USERNAME
#RUN git clone https://github.com/ignatpenshin/colmap-pcd
COPY . /home/$USERNAME/colmap-pcd
WORKDIR /home/$USERNAME/colmap-pcd    
RUN mkdir build && \
cd build && \
cmake .. && \
make -j8 && \
sudo make install

USER $USERNAME
