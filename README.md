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

2. Compile the kernel:

    ```
    make
    ```

    This will generate the raw kernel image.

3. Package the kernel into an ISO:

    ```
    ./package.sh
    ```

    This script will create an ISO image containing the kernel.

4. Run the kernel using QEMU or your preferred virtualization software.

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

