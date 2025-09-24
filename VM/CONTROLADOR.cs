using UnityEngine;
using System.IO;
using System;
using System.Linq.Expressions; // Añade esto con los otros using al principio del archivo


public class CONTROLADOR : MonoBehaviour
{
    [SerializeField] private AudioSource revAudioSource;
    [SerializeField] private AudioClip revSound;
    [SerializeField] private AudioSource idleAudioSource;
    [SerializeField] private AudioClip idleSound;
    [SerializeField] private AudioSource beepAudioSource;
    [SerializeField] private AudioClip beepSound;// Drag your rev sound here
    [SerializeField] private AudioSource lightAudioSource;
    [SerializeField] private AudioClip lightSound;//
    
    //public FileStream nombre;
    public float scaleFactor = 1.0f; // Ajusta este valor según necesites
    public VirtualMachine vm;
    private bool vmInitialized = false;
    private float executionInterval = 0.25f; // Ejecutar cada 0.1 segundos
    private float timeSinceLastExecution = 0f;

    // Start is called before the first execution of Update after the MonoBehaviour is created
    // 1. Mueve tu archivo a: 
    //    `Assets/Resources/object.bin`

    // 2. Código para leerlo:
    public void Start()
    {
    string filePath = Path.Combine(Application.streamingAssetsPath, "object.bin");

        vm = new VirtualMachine();

        if (File.Exists(filePath))
        {
            vm.LoadProgramInMemory(filePath);
            vm.InitialConditions(); // Configura posición inicial
            vmInitialized = true;  // Habilita la ejecución
            Debug.Log("VM inicializada y programa cargado.");
        }
        else
        {
            Debug.LogError("Archivo no encontrado: " + filePath);
        }
    }
    // Update is called once per frame
    public void Update()
    {
        if (!vmInitialized) return;

        // Ejecutar la VM a intervalos regulares en lugar de cada frame
        timeSinceLastExecution += Time.deltaTime;
        if (timeSinceLastExecution >= executionInterval)
        {
            timeSinceLastExecution = 0f;
            ExecuteVMStep();
        }

        if (vm.taxi.status == VirtualMachine.TAXI_STATUS_ACTIVE)
        {
            if (idleAudioSource.isPlaying == false)
            {
                idleAudioSource.Play();
            }
        }
        else
        {
            idleAudioSource.Stop();
        }
    }

    public void ExecuteVMStep()
    {
        // Ejecutar un paso de la máquina virtual
        if (vm.PC < VirtualMachine.MEMORY_MAX_SIZE && vm.mem[vm.PC] != VirtualMachine.A_END)
        {
            vm.IR1 = vm.mem[vm.PC++];

            switch (vm.IR1)
            {
                case VirtualMachine.A_MOV:
                    vm.i_mov();
                    break;
                case VirtualMachine.A_ADV:
                    vm.i_adv();
                    UpdatetaxiPosition();
                    break;
                case VirtualMachine.A_DEC:
                    vm.i_dec();
                    break;
                case VirtualMachine.A_JNZ:
                    vm.i_jnz();
                    break;
                case VirtualMachine.A_JEZ:
                    vm.i_jez();
                    break;
                case VirtualMachine.A_PUSH:
                    vm.i_push();
                    break;
                case VirtualMachine.A_CMP:
                    vm.i_cmp();
                    break;
                case VirtualMachine.A_END:
                    vm.i_end();
                    break;
                case VirtualMachine.A_TRIGHT:
                    vm.i_tright();
                    UpdatetaxiRotation();
                    break;
                case VirtualMachine.A_TLEFT:
                    vm.i_tleft();
                    UpdatetaxiRotation();
                    break;
                case VirtualMachine.A_DROWN:
                    Debug.Log("drown");
                    vm.i_drown();
                    break;
                case VirtualMachine.A_REV:
                    revAudioSource.PlayOneShot(revSound);
                    vm.i_rev();
                    break;
                case VirtualMachine.A_LIGHTON:
                    lightAudioSource.PlayOneShot(lightSound);
                    vm.i_lighton();
                    break;
                case VirtualMachine.A_LIGHTOFF:
                    lightAudioSource.PlayOneShot(lightSound);
                    vm.i_lightoff();
                    break;
                case VirtualMachine.A_HONK:
                    beepAudioSource.PlayOneShot(beepSound);
                    vm.i_honk();
                    break;
                case VirtualMachine.A_FRWRD:
                    vm.i_frwd();
                    UpdatetaxiPosition();
                    break;
                case VirtualMachine.A_BACK:
                    vm.i_back();
                    UpdatetaxiPosition();
                    break;

            }

            // Actualizar la representación visual si es necesario
            UpdateVisuals();
        }
    }

    public void UpdatetaxiPosition()
    {
        transform.position = new Vector3(
            vm.taxi.pos.x * scaleFactor,
            0.2416726f,
            vm.taxi.pos.y * scaleFactor
        );
    }

   

    public void UpdatetaxiRotation()
    {
        // Actualizar la rotación basada en la orientación
        Vector3 newRotation = Vector3.zero;
        switch (vm.taxi.orient)
        {
            case VirtualMachine.D_EAST:
                newRotation.y = 0f;
                break;
            case VirtualMachine.D_WEST:
                newRotation.y = 180f;
                break;
            case VirtualMachine.D_NORTH:
                newRotation.y = 270f;
                break;
            case VirtualMachine.D_SOUTH:
                newRotation.y = 90f;
                break;
        }
        transform.eulerAngles = newRotation;
    }

    public void UpdateVisuals()
    {
        // Aquí puedes actualizar otros elementos visuales como:
        // - Estado del objeto (recogido/suelto)
        // - Obstáculos
        // - Condiciones de la máquina virtual (para depuración)
    }
}

// Clase VirtualMachine adaptada para Unity (sin cambios en la lógica principal)