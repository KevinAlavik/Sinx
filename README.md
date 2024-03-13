# Sinx
*Most of this README has been AI generated, tho its content is true.* 

Sinx is a free to use, simple 32-bit Unix-like kernel developed for educational purposes. It is intended to provide a basic understanding of kernel development concepts and serves as a starting point for learning about operating systems. **Sinx is a Hybrid Kernel "*A hybrid kernel is an operating system kernel architecture that attempts to combine aspects and benefits of microkernel and monolithic kernel architectures used in operating systems.*"**

## Features
- Terminal
- stdio (printf lib)
- GDT (we are working on it)

# Dependencies
- i686-elf-binutils
- i686-elf-gcc
- nasm
- qemu-system-i383 (for running with qemu)

## How to Use

1. Clone the repository:

    ```
    git clone https://github.com/KevinAlavik/Sinx.git
    cd Sinx
    ```
    ![image](https://github.com/KevinAlavik/Sinx/assets/95900603/ab55c3b8-68ce-4de7-b222-23bd9ad36306)


2. Initialize Submodules:
   ```
   git submodule update --init
   ```
   ![image](https://github.com/KevinAlavik/Sinx/assets/95900603/9c55e264-d32b-47c0-b869-45fadc1b1ac8)

   
   This downloads modules like the terminal (`kernel/drivers/display/nighterm`)

3. Compile the kernel:

    ```
    make
    ```
    ![image](https://github.com/KevinAlavik/Sinx/assets/95900603/a03d308b-5c89-4430-87d1-996dbb22c13c)


    This will generate the raw kernel image.

4. Package the kernel into an ISO:

    ```
    make package
    ```
    ![image](https://github.com/KevinAlavik/Sinx/assets/95900603/81e2f068-5fed-4fa3-b09d-cad4f3d137ac)


    This script will create an ISO image containing the kernel and GRUB.

5. Run the kernel using QEMU:
   ```
   make qemu
   ```
   ![image](https://github.com/KevinAlavik/Sinx/assets/95900603/15d34449-ed50-46c1-a88a-5c5f39b00463)

   ^^^ This might look different in the future. (Mostly more boot logs)
   
   In the future there will be targets to run Sinx in other emulators.

## What to do next?
Just explore, right now there is nothing much in the OS so just be patient :)

## Contributing

Contributions to Sinx are welcome! Feel free to submit pull requests for bug fixes, improvements, or new features. For major changes, please open an issue first to discuss potential updates.

## Acknowledgements

Sinx is inspired by various educational resources and tutorials available online. Special thanks to the developers and contributors of the following projects:

- GRUB
- QEMU
- Multiboot protocol

## Thanks to lolguy91 and his OS dev server!
If you have had a unpleasant time in the regular OS dev server, aka they are not very helpful. Well now there is a non toxic and newbie friendly server in town: [The Less-Toxic OSDev Server](https://discord.gg/RgPdpDBDTM)

## Pronunciation

The name "Sinx" is pronounced just like "sinks" (/sɪŋks/).

## Disclaimer

Sinx is developed for educational purposes and is provided as-is, without any warranty. Use at your own risk.

## Credits
- [Nighterm](https://github.com/schkwve/nighterm-extended): Powers most of the non GUI terminal stuff.

## Sponsors

This project is an open-source endeavor driven by passion and dedication. We do not generate revenue from our work. As a sole developer, I personally fund this project's development and maintenance. However, your support through sponsorship can greatly assist in its sustainability and growth.

[![Sponsor on GitHub](https://img.shields.io/badge/Sponsor-GitHub-red?logo=github)](https://github.com/sponsors/KevinAlavik)

Your sponsorship helps ensure the continued improvement and sustainability of this project. Thank you for considering supporting us!


## License

Sinx is licensed under the GNU General Public License v3.0 (GPL-3.0). See the [LICENSE](LICENSE) file for details.
