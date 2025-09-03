from havoc import Demon, RegisterCommand

def killPID(demonID, *param):
  TaskID : str    = None
  demon  : Demon  = None
  packer : Packer = Packer()

  pid: int = 0

  demon = Demon(demonID)

  if len(param) < 1:
    demon.ConsoleWrite(demon.CONSOLE_ERROR, f"Not enough arguments {len(param)}")
    return False

  if len(param) > 1:
    demon.ConsoleWrite(demon.CONSOLE_ERROR, "Too many arguments")
    return False

  pid = int(param[0])

  if pid < 1:
    demon.ConsoleWrite(demon.CONSOLE_ERROR, f"Wrong PID value: {pid}")
    return False

  TaskID = demon.ConsoleWrite(demon.CONSOLE_TASK, f"Tasked demon to kill process with PID {pid}.")

  packer.addint(pid)

  demon.InlineExecute(TaskID, "go", "killerPID-BOF.x64.o", packer.getbuffer(), False)

  return TaskID

RegisterCommand(killPID, "", "killerPID", "kill a process by PID", 0, "[PID]", "1234")
