// Allows for several view implementations
class ITotoOutput {

    public:
        virtual void welcomeMessage() = 0;
        virtual void programUsage() = 0;

        virtual void imageCompressing() = 0;
        virtual void imageDecompressing() = 0;

        virtual void displayPSNR(float psnr) = 0;

        virtual void progressBar(int percentage) = 0;

        virtual void imageCompressionEnded() = 0;
        virtual void imageDecompressionEnded() = 0;
        
        ITotoOutput() {};
        virtual ~ITotoOutput() {};
};
