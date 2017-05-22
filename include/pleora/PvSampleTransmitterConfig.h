// *****************************************************************************
//
//     Copyright (c) 2012, Pleora Technologies Inc., All rights reserved.
//
// -----------------------------------------------------------------------------
//
// Common configuration for all transmitter samples.
//
// *****************************************************************************

#ifndef __PV_TRANSMITTER_SAMPLE_CONFIG_H__
#define __PV_TRANSMITTER_SAMPLE_CONFIG_H__

#include <PvSampleUtils.h>
#include <PvSystem.h>
#include <PvNetworkAdapter.h>
#include <map>


// Default values
#define DEFAULT_WIDTH ( 640 )
#define DEFAULT_HEIGHT ( 480 )
#define DEFAULT_NO_PATTERN ( false )
#define DEFAULT_STRIPS_BY_IMAGE ( DEFAULT_WIDTH / DEFAULT_HEIGHT )
#define DEFAULT_PIXEL_TYPE ( PvPixelMono8 )
#define DEFAULT_PIXEL_TYPE_NAME ( "PvPixelMono8" )
#define DEFAULT_STRIPS_COLOR_GRADIANT ( 16 )
#define DEFAULT_MAXIMUM_CHUNK_SIZE ( 128 )
#define DEFAULT_NUMBER_OF_BUFFERS ( 48 )
#define DEFAULT_NUMBER_OF_BUFFERS_PENDING_FOR_RESENDS ( 32 )
#define DEFAULT_NUMBER_OF_PENDING_RESEND_REQUESTS ( 64 )
#define DEFAULT_SOURCE_ADDRESS ( "" )
#define DEFAULT_DESTINATION_ADDRESS ( "239.192.1.1" )
#define DEFAULT_DESTINATION_PORT ( 1042 )
#define DEFAULT_SOURCE_PORT ( 0 )
#define DEFAULT_BUFFER_COUNT ( 4 )
#define DEFAULT_PACKET_SIZE ( 1440 )
#define DEFAULT_SILENT ( false )
#define DEFAULT_FPS ( 30 )


#ifndef PV_GENERATING_DOXYGEN_DOC


// Application config
class PvSampleTransmitterConfig
{
public:

    PvSampleTransmitterConfig()
    {
        SetDefaults();
    }

    ~PvSampleTransmitterConfig()
    {
    }

    const char *GetSourceAddress() const { return mSourceAddress.c_str(); }
    uint16_t GetSourcePort() const { return mSourcePort; }
    const char *GetDestinationAddress() const { return mDestinationAddress.c_str(); }
    uint16_t GetDestinationPort() const { return mDestinationPort; }
    float GetFPS() const { return mFPS; }
    uint32_t GetPacketSize() const { return mPacketSize; }
    uint32_t GetBufferCount() const { return mBufferCount; }
    bool GetSilent() const { return mSilent; }
    uint32_t GetWidth() const { return mWidth; }
    uint32_t GetHeight() const { return mHeight; }
    bool GetNoPattern() const { return mNoPattern; }
    uint32_t GetStripsByImage() const { return mStripsByImage; }
    PvPixelType GetPixelType() const { return mPixelType; }
    uint32_t GetStripsColorGradiant() const { return mStripsColorGradiant; }
    uint32_t GetMaximumChunkSize() const { return mMaximumChunkSize; }
    uint32_t GetNumberOfBuffers() const { return mNumberOfBuffers; }
    uint32_t GetNumberOfBuffersPendingForResends() const { return mNumberOfBuffersPendingForResends; }
    uint32_t GetNumberOfPendingResendRequests() const { return mNumberOfPendingResendRequests; }

    void SetDefaults()
    {
        // Only used to enumerate network interfaces, no need to call Find
        PvSystem lSystem;

        // Find default source address
        bool lFound = false;
        for ( uint32_t i = 0; i < lSystem.GetInterfaceCount() && !lFound; i++ )
        {
            const PvNetworkAdapter *lNetworkAdapter = dynamic_cast<const PvNetworkAdapter *>( lSystem.GetInterface( i ) );
            if ( lNetworkAdapter == NULL )
            {
                continue;
            }

            uint32_t lIPCount = lNetworkAdapter->GetIPAddressCount();
            for ( uint32_t j = 0; j < lIPCount; j++ )
            {
                PvString lIP = lNetworkAdapter->GetIPAddress( j );
                if ( strcmp( "0.0.0.0", lIP.GetAscii() ) != 0 )
                {
                    mSourceAddress = lIP.GetAscii();
                    lFound = true;
                }
            }
        }
        if ( !lFound )
        {
            cout << "No valid interfaces found." << endl;
            exit( 1 );
        }

        // Set static defaults
        mDestinationAddress = DEFAULT_DESTINATION_ADDRESS;
        mDestinationPort = DEFAULT_DESTINATION_PORT;
        mSourcePort = DEFAULT_SOURCE_PORT;
        mPacketSize = DEFAULT_PACKET_SIZE;
        mBufferCount = DEFAULT_BUFFER_COUNT;
        mSilent = DEFAULT_SILENT;
        mFPS = DEFAULT_FPS;
        mWidth = DEFAULT_WIDTH;
        mHeight = DEFAULT_HEIGHT;
        mNoPattern = DEFAULT_NO_PATTERN;
        mStripsByImage = DEFAULT_STRIPS_BY_IMAGE;
        mPixelType = DEFAULT_PIXEL_TYPE;
        mStripsColorGradiant = DEFAULT_STRIPS_COLOR_GRADIANT;
        mMaximumChunkSize = DEFAULT_MAXIMUM_CHUNK_SIZE;
        mNumberOfBuffers = DEFAULT_NUMBER_OF_BUFFERS;
        mNumberOfBuffersPendingForResends = DEFAULT_NUMBER_OF_BUFFERS_PENDING_FOR_RESENDS;
        mNumberOfPendingResendRequests = DEFAULT_NUMBER_OF_PENDING_RESEND_REQUESTS;
        // construct the pixel format map for command line arguments
        PvPixelType lPixelTypes[] = 
        {
            PvPixelMono8,
            PvPixelMono10,
            PvPixelMono12,
            PvPixelMono16,
            PvPixelRGB8,
            PvPixelRGBa8,
        };

        string lPixelTypeNames[] = 
        {
            "PvPixelMono8",
            "PvPixelMono10",
            "PvPixelMono12",
            "PvPixelMono16",
            "PvPixelRGB8",
            "PvPixelRGBa8",
        };

        for( int i = 0 ; i < sizeof( lPixelTypes ) / sizeof( PvPixelType ); i ++ )
        {
            mPixelFormatMap.insert( make_pair( lPixelTypeNames[i], lPixelTypes[i] ) );
        }
    }

    void ParseCommandLine( int aCount, const char **aArgs )
    {
        if ( ParseOptionFlag( aCount, aArgs, "--help" ) )
        {
            PrintHelp();
            exit( 0 );
        }

        ParseOption<float>( aCount, aArgs, "--fps", mFPS );
        ParseOption<uint32_t>( aCount, aArgs, "--packetsize", mPacketSize );
        ParseOption<string>( aCount, aArgs, "--destinationaddress", mDestinationAddress );
        ParseOption<uint16_t>( aCount, aArgs, "--destinationport", mDestinationPort );
        ParseOption<string>( aCount, aArgs, "--sourceaddress", mSourceAddress );
        ParseOption<uint16_t>( aCount, aArgs, "--sourceport", mSourcePort );
        ParseOption<uint32_t>( aCount, aArgs, "--buffercount", mBufferCount );
        ParseOptionFlag( aCount, aArgs, "--silent", &mSilent );

        ParseOption<uint32_t>( aCount, aArgs, "--width", mWidth );
        ParseOption<uint32_t>( aCount, aArgs, "--height", mHeight );
        ParseOptionFlag( aCount, aArgs, "--nopattern", &mNoPattern );
        ParseOption<uint32_t>( aCount, aArgs, "--strips", mStripsByImage );
        string lColorName;
        ParseOption<string>( aCount, aArgs, "--color", lColorName );
        map<string, PvPixelType>::iterator lIt = mPixelFormatMap.find( lColorName );
        if( lIt != mPixelFormatMap.end() )
        {
            mPixelType = lIt->second;
        }

        ParseOption<uint32_t>( aCount, aArgs, "--gradiant", mStripsColorGradiant );
        ParseOption<uint32_t>( aCount, aArgs, "--chunk", mMaximumChunkSize );
        ParseOption<uint32_t>( aCount, aArgs, "--buffers", mNumberOfBuffers );
        ParseOption<uint32_t>( aCount, aArgs, "--resendbuffers", mNumberOfBuffersPendingForResends );
        ParseOption<uint32_t>( aCount, aArgs, "--resends", mNumberOfPendingResendRequests );
        if ( mDestinationPort == 0 )
        {
            cout << "Please enter a destination port." << endl;
            cin >> mDestinationPort;
        }
    }

    void PrintHelp()
    {
        cout << "Optional command line arguments:" << endl << endl;

        cout << "--help " << endl << "Print this help message." << endl << endl;

        cout << "--packetsize=<maximimum size of streaming packets>" << endl;
        cout << "Default: 1440 For best results, set \"Jumbo Frames\" property on your NIC and increase this value accordingly." << endl << endl;

        cout << "--destinationaddress=<destination address in the form 123.456.789.101>" << endl;
        cout << "Default: " << DEFAULT_DESTINATION_ADDRESS << endl << endl;

        cout << "--destinationport=<destination port>" << endl;
        cout << "Default: " << DEFAULT_DESTINATION_PORT << endl << endl;

        cout << "--sourceaddress=<source address in the form 123.456.789.101>" << endl;
        cout << "Default: first valid address encountered while enumerating interfaces" << endl << endl;

        cout << "--sourceport=<source port>" << endl;
        cout << "Default: " << DEFAULT_SOURCE_PORT << " - a port is automatically assigned when the socket is opened" << endl << endl;

        cout << "--buffercount=<number of transmit buffers to use>" << endl;
        cout << "Default: " << DEFAULT_BUFFER_COUNT << " - increase this number when sending smaller images at high frame rates." << endl << endl;

        cout << "--silent" << endl;
        cout << "Don't wait for a key press." << endl;
        cout << "By default, the system waits for a key press before it begins transmitting. " << endl << endl;

        cout << "--width=<width in pixels>" << endl;
        cout << "Default: " << DEFAULT_WIDTH << endl << endl;

        cout << "--height=<height in pixels>" << endl;
        cout << "Default: " << DEFAULT_HEIGHT << endl << endl;

        cout << "--nopattern" << endl;
        cout << "Disables the test pattern." << endl << endl;

        cout << "--fps=<frame per second>" << endl;
        cout << "Default: " << DEFAULT_FPS << endl << endl;

        cout << "--strips=<number of strips by image>" << endl;
        cout << "Default: " << DEFAULT_STRIPS_BY_IMAGE << endl << endl;

        cout << "--color=<pixel format>" << endl;
        cout << "Default: " << DEFAULT_PIXEL_TYPE_NAME << endl << endl;

        cout << "--gradiant=<color gradiant>" << endl;
        cout << "Default: " << DEFAULT_STRIPS_COLOR_GRADIANT << endl << endl;

        cout << "--chunk=<maximum chunk size>" << endl;
        cout << "Default: " << DEFAULT_MAXIMUM_CHUNK_SIZE << endl << endl;

        cout << "--buffers=<number of buffers to be allocated>" << endl;
        cout << "Default: " << DEFAULT_MAXIMUM_CHUNK_SIZE << endl << endl;

        cout << "--resendbuffers=<number of buffers held for resend>" << endl;
        cout << "Default: " << DEFAULT_NUMBER_OF_BUFFERS_PENDING_FOR_RESENDS << endl << endl;

        cout << "--resends=<number of pending resend requests>" << endl;
        cout << "Default: " << DEFAULT_NUMBER_OF_PENDING_RESEND_REQUESTS << endl << endl;
        cout << "By default, each frame is populated with test data - this takes a little bit of CPU power so for pure benchmark purposes it may be advisable to disable this behaviour." << endl << endl;

    }

private:

    string mSourceAddress;
    uint16_t mSourcePort;

    string mDestinationAddress;
    uint16_t mDestinationPort;

    float mFPS;

    uint32_t mPacketSize;
    uint32_t mBufferCount;

    bool mSilent;

    uint32_t mWidth;
    uint32_t mHeight;
    bool mNoPattern;
    uint32_t mStripsByImage;
    PvPixelType mPixelType;
    uint32_t mStripsColorGradiant;
    uint32_t mMaximumChunkSize;
    uint32_t mNumberOfBuffers;
    uint32_t mNumberOfBuffersPendingForResends;
    uint32_t mNumberOfPendingResendRequests;
    map<string, PvPixelType> mPixelFormatMap;
};


#endif // PV_GENERATING_DOXYGEN_DOC


#endif // __PV_TRANSMITTER_SAMPLE_CONFIG_H__

