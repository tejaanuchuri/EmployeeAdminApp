using System;
using System.Collections.Generic;
using System.Data.OleDb;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfControlLibrary
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class UserControl1 : UserControl
    {
        const string nativeLibDllPath = "C:\\Users\\admin.teja\\Videos\\AdminApp\\Release\\DatabaseLibrary.dll";


        [DllImport(nativeLibDllPath, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern IntPtr GetEmp();
        public List<EmployeeRecord> EmployeeRecords = new List<EmployeeRecord>();

        public UserControl1()
        {
            InitializeComponent();
            // LoadEmployeeRecordsOnGrid();
            IntPtr result = GetEmp();
            EmpData[] empArr = new EmpData[10];
            MarshalUnmananagedArray2Struct<EmpData>(result, 10, out empArr);
            for (int i = 0; i < empArr.Length; i++)
            {
                EmpData empData = empArr[i];
                EmployeeRecords.Add(new EmployeeRecord
                {
                    Address = empData.Address,
                    Age = empData.Age,
                    DateOfBirth = empData.DateOfBirth,
                    Email = empData.Email,
                    FirstName = empData.FirstName,
                    Gender = empData.Gender,
                    HireDate = empData.HireDate,
                    Id = empData.Id,
                    JobTitle = empData.JobTitle,
                    LastName = empData.LastName,
                    MobileNumber = empData.MobileNumber,
                    Salary = empData.Salary,
                    Title = empData.Title,
                    YearsOfExperience = empData.YearsOfExperience
                });

            }
            datagrid.ItemsSource = EmployeeRecords.AsEnumerable<EmployeeRecord>();
        }

        public static T[] MarshalUnmananagedArray2Struct<T>(IntPtr unmanagedArray, int length, out T[] mangagedArray)
        {
            var size = Marshal.SizeOf(typeof(T));
            mangagedArray = new T[length];

            for (int i = 0; i < length; i++)
            {
                IntPtr ins = new IntPtr(unmanagedArray.ToInt64() + i * size);
                mangagedArray[i] = Marshal.PtrToStructure<T>(ins);
            }

            return mangagedArray;
        }
    }
    [StructLayout(LayoutKind.Sequential), Serializable]
    public struct EmpData
    {
        [MarshalAs(UnmanagedType.I4)]
        public int Id;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string FirstName;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string LastName;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string MobileNumber;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string HireDate;

        [MarshalAs(UnmanagedType.I4)]
        public int YearsOfExperience;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string DateOfBirth;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string Title;

        [MarshalAs(UnmanagedType.I4)]
        public int Age;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string Gender;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string Email;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string Address;

        [MarshalAs(UnmanagedType.LPTStr)]
        public string JobTitle;

        [MarshalAs(UnmanagedType.R8)]
        public double Salary;
    }

    public class EmployeeRecord
    {
        public int Id { set; get; }
        public string FirstName { set; get; }
        public string LastName { set; get; }
        public string MobileNumber { set; get; }
        public string HireDate { set; get; }
        public int YearsOfExperience { set; get; }
        public string DateOfBirth { set; get; }
        public string Title { set; get; }
        public int Age { set; get; }
        public string Gender { set; get; }
        public string Email { set; get; }
        public string Address { set; get; }
        public string JobTitle { set; get; }
        public double Salary { set; get; }
        public EmployeeRecord(int id, string firstname, string lastname)
        {
            Id = id;
            FirstName = firstname;
            LastName = lastname;
        }
        public EmployeeRecord()
        {
            Id = -1;
            FirstName = "";
            LastName = "";
            MobileNumber = "";
            HireDate = "";
            YearsOfExperience = 0;
            DateOfBirth = "";
            Title = "";
            Age = 0;
            Gender = "";
            Email = "";
            Address = "";
            JobTitle = "";
            Salary = 0.0;
        }
    }
}
