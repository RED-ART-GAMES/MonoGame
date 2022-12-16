#include <stdio.h>

//#include <mono/mini/jit.h>
//#include <mono/metadata/mono-debug.h>
//#define HAS_MONO_IMPORTS

#if _DEBUG
#include "../../aot/Debug/mono-aot.h"
#else
#include "../../aot/Release/mono-aot.h"
#endif

unsigned int sceLibcHeapDelayedAlloc = 1;
unsigned int sceLibcHeapExtentededAlloc = 1;
size_t sceLibcHeapSize = 200 * 1024 * 1024; //0xffffffffffffffffUL; // SCE_LIBC_HEAP_SIZE_EXTENDED_ALLOC_NO_LIMIT
size_t sceLibcHeapInitialSize = 200 * 1024 * 1024; // Initial heap is 200Mb

/*
static void debugger_setup()
{
	char *args[1];
	char buff[1000];
	int loglevel = 10;
	const char *host = "192.168.0.108";
	int port = 9000;
	int server = 0;

	sprintf (buff,
		"--debugger-agent=transport=dt_socket,loglevel=%d,address=%s:%d,%sembedding=1", 
		loglevel, 
		host,
		port,
		server ? "server=y," : "");

	args [0] = buff;
	mono_jit_parse_options(1, args);
	mono_debug_init(MONO_DEBUG_FORMAT_MONO);
}
*/

int main (int argc, char *argv[])
{
	MonoAssembly *assembly;

	g_setenv("MONO_USE_DIRECT_MEMORY", "1", 1);
	g_setenv("MONO_PATH", "/app0/", 1); /*FIXME this doesn't affect the location in main_assembly_name */
	//g_setenv ("MONO_LOG_LEVEL", "debug", 1);
	g_setenv("MONO_GC_PARAMS", "nursery-size=1m", 1);
	//g_setenv ("MONO_GC_DEBUG", "2", 1);
#if _DEBUG
	//g_setenv("MONO_IGNORE_SUSPEND_TIMEOUT", "1", 1);
#endif

	orbis_setup();
	orbis_register_modules();
	mono_jit_set_aot_only(1);

	//debugger_setup();

	mono_jit_init_version ("ORBIS", "v2.0.50727");
	assembly = mono_assembly_open(main_assembly_name, NULL);
	mono_jit_exec(mono_domain_get(), assembly, argc, argv);

	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// HACK:  This is to work around linker problems in Mono.PS4!

// System.Internals.dll
extern void OutputDebugString(char* lpOutputString) { }
extern void EventWriteString(char* lpOutputString) { }
extern void ReportEvent(char* lpOutputString) { }
extern void EventActivityIdControl(char* lpOutputString) { }
extern void RegisterEventSource() { }
extern void EventWriteTransfer() { }
extern void EventWrite() { }
extern void EventEnabled() { }
extern void EventUnregister() { }
extern void EventRegister() { }
extern void DebugBreak() { }
extern void IsDebuggerPresent() { }
extern void GetComputerNameEx() { }
extern void GetSystemTimeAsFileTime() { }
extern void GetSystemTimeAdjustment() { }
extern void QueryPerformanceCounter() { }
extern void SetWaitableTimer() { }
extern void CreateWaitableTimer() { }
extern void DeregisterEventSource() { }

// System.dll
extern void CreateZStream() {}
extern void CloseZStream() {}
extern void Flush() {}
extern void ReadZStream() {}
extern void WriteZStream() {}
extern void getdomainname() {}
extern void dlopen() {}
extern void dlclose() {}
extern void dlsym() {}
extern void CFRelease() {}
extern void CFRunLoopGetMain() {}
extern void SCNetworkReachabilityCreateWithAddress() {}
extern void SCNetworkReachabilityGetFlags() {}
extern void SCNetworkReachabilitySetCallback() {}
extern void SCNetworkReachabilityScheduleWithRunLoop() {}
extern void SCNetworkReachabilityUnscheduleFromRunLoop() {}
extern void CreateNLSocket() {}
extern void ReadEvents() {}
extern void CloseNLSocket() {}
extern void if_nametoindex() {}
extern void getifaddrs() {}
extern void freeifaddrs() {}
extern void capget() {}
extern void CFRetain() {}
extern void CFArrayCreate() {}
extern void CFArrayGetCount() {}
extern void CFArrayGetValueAtIndex() {}
extern void CFNumberGetValue() {}
extern void CFStringCreateWithCharacters() {}
extern void CFStringGetLength() {}
extern void CFStringGetCharactersPtr() {}
extern void CFStringGetCharacters() {}
extern void CFDictionaryGetValue() {}
extern void CFURLCreateWithString() {}
extern void CFRunLoopAddSource() {}
extern void CFRunLoopRemoveSource() {}
extern void CFRunLoopRunInMode() {}
extern void CFRunLoopGetCurrent() {}
extern void CFRunLoopStop() {}
extern void CFNetworkCopyProxiesForAutoConfigurationScript() {}
extern void CFNetworkExecuteProxyAutoConfigurationURL() {}
extern void CFNetworkCopyProxiesForURL() {}
extern void CFNetworkCopySystemProxySettings() {}
extern void SecCertificateCreateWithData() {}
extern void SecTrustCreateWithCertificates() {}
extern void SecTrustSetAnchorCertificates() {}
extern void SecPolicyCreateSSL() {}
extern void SecTrustEvaluate() {}
extern void CFDataCreate() {}
extern void uname() {}
