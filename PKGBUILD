# Maintainer: Your Name <youremail@domain.com>
pkgname=Varnook
pkgver=0.1
pkgrel=1
pkgdesc="cubo"
url="https://github.com/Varnook/cubituSDL.git"
arch=(x86_64)
depends=('sdl2')
makedepends=('make')
source=("git+$url")
md5sums=('SKIP')

build() {
	cd "cubituSDL"
	./configure --prefix=/usr
	make
}

package() {
	make DESTDIR="$pkgdir/" install
}
