
public sealed class Singleton
{
    private Singleton()
    {
    }

    public static Singleton instance
    {
        get
        {
            return Nested.instance;
        }
    }

    class Nested
    {
        static Nested()
        {

        }
     
        internal static readonly Singleton instance = new Singleton();
    }
}