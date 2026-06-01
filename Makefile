BUILD_DIR := build

.PHONY: all build clean deps configure deb

all: build

deps:
	sudo apt-get install -y \
		qtbase5-dev \
		libkf5windowsystem-dev \
		libkf5globalaccel-dev \
		libkf5i18n-dev \
		libkf5widgetsaddons-dev \
		libkf5xmlgui-dev \
		libkf5config-dev \
		libkf5configwidgets-dev \
		libqt5svg5-dev \
		libqt5x11extras5-dev \
		extra-cmake-modules \
		libxcb-ewmh-dev \
		libxcb-icccm4-dev \
		cmake \
		g++ \
		debhelper \
		fakeroot

configure: $(BUILD_DIR)/Makefile

$(BUILD_DIR)/Makefile: CMakeLists.txt src/CMakeLists.txt
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug

build: $(BUILD_DIR)/Makefile
	cmake --build $(BUILD_DIR) -j$$(nproc)

clean:
	rm -rf $(BUILD_DIR)

install: build
	cmake --install $(BUILD_DIR)

deb:
	dpkg-buildpackage --root-command=fakeroot --build=binary --unsigned-buildinfo --unsigned-changes
