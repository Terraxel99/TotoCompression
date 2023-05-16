#include "TotoConsoleOutput.hpp"

void TotoConsoleOutput::welcomeMessage() {
    cout << "\033[1;36mWelcome to Toto's compression !\033[0m" << endl << endl;
}

void TotoConsoleOutput::programUsage() {
    cout << "\033[31mProgram usage :" << endl;
    cout << "\t--help\t\t\t: To get help about the program" << endl;
    cout << "\t--compress {input_path} [-o {output_path}]\t: To compress the image at {input_path} and save to {output_path} (optional)." << endl;
    cout << "\t--decompress {input_path} [-o {output_path}]\t: To decompress the image at {input_path} and save to {output_path} (optional).\033[0m" << endl;
}

void TotoConsoleOutput::imageCompressing() {
    cout << "\033[36mStarting image compression\033[0m" << endl;
}

void TotoConsoleOutput::imageDecompressing() {
    cout << "\033[36mStarting image decompression\033[0m" << endl;
}

void TotoConsoleOutput::imageCompressionEnded() {
    cout << "\033[32mImage has been successfully compressed\033[0m" << endl;
}

void TotoConsoleOutput::imageDecompressionEnded() {
    cout << "\033[32mImage has been successfully decompressed\033[0m" << endl;
}

void TotoConsoleOutput::progressBar(int percentage) {
    percentage = percentage > 100 ? 100 : percentage;
    percentage = percentage < 0 ? 0 : percentage;

    int nbCharacters = percentage / PROGRESSBAR_UNIT;
    int maxCharacters = (100 / PROGRESSBAR_UNIT);

    cout << "\033[1;37mProgress :\033[0m ";

    cout << "\033[1;37m[\033[0m";

    for (int i = 0; i < nbCharacters; i++) {
        cout << "\033[1;32m█\033[0m";
    }

    for (int i = 0; i < (maxCharacters - nbCharacters); i++) {
        cout << " ";
    }

    cout << "\033[1;37m] " << percentage << " %\033[0m\r";

    if (percentage == 100) {
        cout << endl;
    }

    cout.flush();
}
