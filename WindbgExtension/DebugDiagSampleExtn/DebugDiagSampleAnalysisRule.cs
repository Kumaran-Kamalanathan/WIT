using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Diagnostics.Runtime;
using DebugDiag.DotNet;
using DebugDiag.DotNet.AnalysisRules;


namespace DebugDiagSampleAnalysisRule
{
    public class DebugDiagSampleAnalysisRule : IAnalysisRuleMetadata,IHangDumpRule
    {
        public string Category
        {
            get
            {
                return "Sample Category";
            }
        }

        public string Description
        {
            get
            {
                return "DebugDiag Sample Rule";
            }
        }

        public void RunAnalysisRule(NetScriptManager manager, NetDbgObj debugger, NetProgress progress)
        {
            if (debugger.ClrRuntime == null)
            {
                return;
            }



            #region Sample Code to list Large Objects on Heap

            manager.WriteNameValuePair("PID", debugger.ProcessID.ToString());
            ClrHeap heap = debugger.ClrHeap;
            Dictionary<string, int> lohtype = new Dictionary<string, int>();
            foreach (var heapobj in heap.EnumerateObjects())
            {
                ClrType type = heap.GetObjectType(heapobj);
                if (type.GetSize(heapobj) > 85000)
                {
                    if (lohtype.ContainsKey(type.Name))
                    {
                        lohtype[type.Name]++;
                    }
                    else
                    {
                        lohtype.Add(type.Name, 1);
                    }
                }

            }


            foreach (var item in lohtype)
            {
                manager.WriteLine(item.Key + " " + item.Value, true, "green");
            }

            #endregion

        }
    }
}
