package JSqueak.monitor;

public interface Monitor {
	public void logMessage(String message);
	public void fine(String debugMessage);
	public void finer(String debugMessage);
	public void finest(String debugMessage);
}
