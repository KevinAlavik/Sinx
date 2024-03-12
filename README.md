# Sinx

Sinx is a simple 32-bit Unix-like kernel developed for educational purposes. It is intended to provide a basic understanding of kernel development concepts and serves as a starting point for learning about operating systems.

## Features

- Supports Multiboot2 protocol
- Bootloader: GRUB

## How to Use

1. Clone the repository:

    ```
    git clone https://github.com/KevinAlavik/Sinx.git
    cd Sinx
    ```

2. Initialize Submodules:
   ```
   git submodule update --init
   ```
   
   This downloads modules like the terminal (`kernel/drivers/display/nighterm`)

3. Compile the kernel:

    ```
    make
    ```

    This will generate the raw kernel image. If this failes see **Important**

4. Package the kernel into an ISO:

    ```
    ./tools/package.sh
    ```

    This script will create an ISO image containing the kernel.

5. Run the kernel using QEMU or your preferred virtualization software.

## Important!
![image](https://github.com/KevinAlavik/Sinx/assets/95900603/213220c4-68a2-47a0-9ded-b6af6731d0ee)
You will see this if its the first time you compile. Dont worry, you just need to run `mkdir bin` and rerun now it should look like this.

![image](https://github.com/KevinAlavik/Sinx/assets/95900603/af501e5e-a122-45a3-b45b-a37f00ee9300)
Then this should be in the root of your Sinx directory

![image](https://github.com/KevinAlavik/Sinx/assets/95900603/d7e5a63b-2b3e-4126-a306-fa50923b76e4)

To run it you could run `./tools/boot.sh` which boots using QEMU. This also builds so no need to run package before, since its ran in the boot script.
It should look something like this:

![image](https://github.com/KevinAlavik/Sinx/assets/95900603/62edb681-49d9-4bcc-acb3-aae04d44db00)

And boom ur in!

## What to do next?
Just explore, right now there is nothing much in the OS so just be patient :)

## Contributing

Contributions to Sinx are welcome! Feel free to submit pull requests for bug fixes, improvements, or new features. For major changes, please open an issue first to discuss potential updates.

## License

Sinx is licensed under the GNU General Public License v3.0 (GPL-3.0). See the [LICENSE](LICENSE) file for details.

## Acknowledgements

Sinx is inspired by various educational resources and tutorials available online. Special thanks to the developers and contributors of the following projects:

- GRUB
- QEMU
- Multiboot2 protocol

## Pronunciation

The name "Sinx" is pronounced just like "sinks" (/sɪŋks/).

## Disclaimer

Sinx is developed for educational purposes and is provided as-is, without any warranty. Use at your own risk.

