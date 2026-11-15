public class Instance
{
    public bool Archivable {get;}
    public string Name {get;}
    public Instance? Parent {get; set;} 

    public Instance(string? name)
    {
        Archivable = true;
        Name = name ?? "Instance";
        Parent = null;
    }

    public void Destroy()
    {
        Parent = null;
    }
}