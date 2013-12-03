package JSqueak.monitor;

import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.util.logging.Logger;

public class TextOnlyMonitor  implements Monitor {

	Logger logger=Logger.getLogger("jsqueak.main");

	public TextOnlyMonitor() throws HeadlessException {

	}

	public void actionPerformed(ActionEvent e) {
	    if ("do_something".equals(e.getActionCommand())) {
	        this.logMessage("Oops! I did it.");
	    }
	}


	@Override
	public void logMessage(String message) {
		logger.info(message);
	}

//	@Override
//	public void setStatus(String status) {
//		lbStatus.setText(status);
//	}

	@Override
	public void fine(String debugMessage) {
		logger.fine(debugMessage);

	}

	@Override
	public void finer(String debugMessage) {
		logger.finer(debugMessage);
	}

	@Override
	public void finest(String debugMessage) {
		logger.finest(debugMessage);
	}

}
