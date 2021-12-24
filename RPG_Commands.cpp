#include "RPG_Commands.h"
#include "RPG_Engine.h"

RPG_Engine* cCommand::g_engine = nullptr;

cScriptProcessor::cScriptProcessor()
{
	bUserControlEnabled = true;
}

void cScriptProcessor::AddCommand(cCommand* cmd)
{
	m_listCommands.push_back(cmd);

}

void cScriptProcessor::ProcessCommands(float fElapsedTime)
{
	//If command(s) are available, halt user control
	bUserControlEnabled = m_listCommands.empty();
	
	if (!m_listCommands.empty())
	{
		//A command is available
		if (!m_listCommands.front()->bCompleted)
		{
			//Command has not been started
			if (!m_listCommands.front()->bStarted)
			{
				m_listCommands.front()->Start();
				m_listCommands.front()->bStarted = true;
			}
			else
				m_listCommands.front()->Update(fElapsedTime);
		}
		else
		{
			//Command has been completed
			delete m_listCommands.front();
			m_listCommands.pop_front();
		}
			
	}
}

//Marks currently active command as complete, form external source
void cScriptProcessor::CompleteCommand()
{
	if (!m_listCommands.empty())
	{
		m_listCommands.front()->bCompleted = true;
	}
}


cCommand_MoveTo::cCommand_MoveTo(cDynamic* object, float x, float y, float duration)
{
	m_fTargetPosX = x;
	m_fTargetPosY = y;
	m_fTimeSoFar = 0.0f;
	m_fDuration = max(duration, 0.001f);
	m_pObject = object;
}

void cCommand_MoveTo::Start()
{
	m_fStartPosX = m_pObject->fPositionX;
	m_fStartPosY = m_pObject->fPositionY;
}

void cCommand_MoveTo::Update(float fElapsedTime)
{
	m_fTimeSoFar += fElapsedTime;
	float t = m_fTimeSoFar / m_fDuration;
	if (t > 1.0f) t = 1.0f;

	m_pObject->fPositionX = (m_fTargetPosX - m_fStartPosX) * t + m_fStartPosX;
	m_pObject->fPositionY = (m_fTargetPosY - m_fStartPosY) * t + m_fStartPosY;
	m_pObject->fVelocityX = (m_fTargetPosX - m_fStartPosX) / m_fDuration;
	m_pObject->fVelocityY = (m_fTargetPosX - m_fStartPosY) / m_fDuration;

	if (m_fTimeSoFar >= m_fDuration)
	{
		//Object has reached destination, so stop
		m_pObject->fPositionX = m_fTargetPosX;
		m_pObject->fPositionY = m_fTargetPosY;
		m_pObject->fVelocityX = 0.0f;
		m_pObject->fVelocityY = 0.0f;
		bCompleted = true;
	}
}

cCommand_ShowDialog::cCommand_ShowDialog(vector<string>line)
{
	vecLines = line;
}

void cCommand_ShowDialog::Start()
{
	g_engine-> ShowDialog(vecLines);
}

