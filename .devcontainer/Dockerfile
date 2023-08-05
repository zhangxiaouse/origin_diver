FROM ros:melodic-perception-bionic
# Args for the non-root user
ARG USERNAME=cyber
ARG USER_UID=1000
ARG USER_GID=$USER_UID
# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
  && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
  && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
  && chmod 0440 /etc/sudoers.d/$USERNAME
# Change repository to SJTU mirror
RUN sed -i 's/http:\/\/archive.ubuntu.com/http:\/\/mirror.sjtu.edu.cn/g' /etc/apt/sources.list
RUN sed -i 's/http:\/\/packages.ros.org/http:\/\/mirror.sjtu.edu.cn/g' /etc/apt/sources.list.d/ros1-latest.list
# Update and install general packages
RUN apt-get update && apt-get upgrade -y\
  && apt-get install -q -y openssh-client vim bash-completion tmux gdb wget
# Update and install gcc-9
RUN  apt-get update && apt-get install -y software-properties-common && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
  && apt-get update  && apt-get install -y gcc-9 g++-9 build-essential
RUN  update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 9 \
  && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 9
# Project related packages
RUN apt-get install -q -y libgoogle-glog-dev libeigen3-dev libyaml-cpp-dev doxygen libgeographic-dev
# Build and install gtest
WORKDIR /usr/src/gtest
RUN cmake . && make && mv libg* /usr/lib/
# ROS related packages
RUN apt-get install  -q -y  ros-melodic-interactive-markers  ros-melodic-marker-msgs ros-melodic-mrpt1  ros-melodic-geodesy 
# install cmake
# RUN wget https://apt.kitware.com/kitware-archive.sh \
#   && bash kitware-archive.sh \
#   && apt-get install -y cmake \
#   && rm kitware-archive.sh \
#   && apt-get clean \
#   && rm -rf /var/lib/apt/lists/*
# Install clang-15
# RUN wget https://apt.llvm.org/llvm.sh \
#   && bash llvm.sh 15 \
#   && rm llvm.sh \
#   && apt-get autoremove -y clang-15 lldb-15 lld-15 \
#   && apt-get clean \
#   && rm -rf /var/lib/apt/lists/* 
# ENV PATH="/usr/lib/llvm-15/bin:${PATH}"
# Build and install mrpt-bridge mrpt-msgs
WORKDIR /home/${USERNAME}/third_party/ws_mrpt/src
RUN git clone https://github.com/mrpt-ros-pkg/mrpt_msgs.git --branch 0.1.23 --single-branch --depth 1
RUN git clone https://github.com/mrpt-ros-pkg/mrpt_bridge.git --branch 0.1.25 --single-branch --depth 1
WORKDIR ..
RUN . /opt/ros/melodic/setup.sh && catkin_make -DCMAKE_INSTALL_PREFIX=/opt/ros/melodic install
# livox SDK
WORKDIR /home/${USERNAME}/third_party
RUN git clone https://github.com/Livox-SDK/Livox-SDK.git --branch v2.3.0 --single-branch  --depth 1
WORKDIR /home/${USERNAME}/third_party/Livox-SDK/build
RUN cmake -G "Unix Makefiles" ..
RUN cmake --build . --target install
RUN ldconfig  
# Prepare for working dir
RUN chown -R $USERNAME /home/${USERNAME}
USER $USERNAME
RUN echo 'source /opt/ros/melodic/setup.bash' >> /home/$USERNAME/.bashrc
COPY cmake-tools-kits.json /home/${USERNAME}/.local/share/CMakeTools/