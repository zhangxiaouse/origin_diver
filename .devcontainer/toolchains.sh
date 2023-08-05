#!/bin/bash
# install latest cmake
sudo bash -c "$(wget -O - https://apt.kitware.com/kitware-archive.sh)"
sudo apt install -y cmake cmake-qt-gui

# install latest clangd
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
sudo update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-15 100