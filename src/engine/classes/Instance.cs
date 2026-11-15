public class Instance
{
    public bool Archivable { get; }
    public string Name { get; }
    private Instance? _parent;
    public Instance? Parent
    {
        get => _parent;
        set => SetParent(value ?? null);
    }
    private List<Instance> _children;

    public Instance(string? name)
    {
        Archivable = true;
        Name = name ?? "Instance";
        _parent = null;
        _children = new();
    }

    public void Destroy()
    {
        _parent = null;
    }

    public void SetParent(Instance? parent)
    {
        if (parent == this)
            throw new InvalidOperationException("An instance cannot parent itself");

        _parent?._children.Remove(this);
        _parent = parent;
        _parent?._children.Add(this);
    }

    public Instance? FindFirstChild(string name, Boolean? recursive)
    {
        recursive = recursive ?? false;
        Instance? child = _children.Find(Child => Child.Name == name);

        if (child != null) return child;
        else return null;
        
    }
}