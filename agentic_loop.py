import subprocess

CMD = 'codex exec --yolo "Follow the instructions in AGENTS.MD."'

while True:
    subprocess.run(CMD, shell=True)
