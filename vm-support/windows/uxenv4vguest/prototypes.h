

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD UxvgEvtDeviceAdd;

EVT_WDF_OBJECT_CONTEXT_CLEANUP UxvgEvtDriverContextCleanup;

EVT_WDF_DEVICE_D0_ENTRY UxvgEvtDeviceD0Entry;
EVT_WDF_DEVICE_D0_EXIT UxvgEvtDeviceD0Exit;
EVT_WDF_DEVICE_PREPARE_HARDWARE UxvgEvtDevicePrepareHardware;
EVT_WDF_DEVICE_RELEASE_HARDWARE UxvgEvtDeviceReleaseHardware;

EVT_WDF_IO_QUEUE_IO_READ UxvgEvtIoRead;
EVT_WDF_IO_QUEUE_IO_WRITE UxvgEvtIoWrite;

EVT_WDF_INTERRUPT_ISR UxvgEvtInterruptIsr;
EVT_WDF_INTERRUPT_DPC UxvgEvtInterruptDpc;
EVT_WDF_INTERRUPT_ENABLE UxvgEvtInterruptEnable;
EVT_WDF_INTERRUPT_DISABLE UxvgEvtInterruptDisable;


NTSTATUS UxvgInterruptCreate( IN PDEVICE_EXTENSION DevExt);

void uxen_v4v_guest_do_plumbing(PDRIVER_OBJECT pdo);
void uxen_v4v_guest_undo_plumbing(void);

