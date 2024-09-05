package dsml.tree.reader;

import java.io.File;
import java.io.IOException;
import java.util.Map;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EcorePackage;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.util.EcoreUtil;
import pk.questlab.dsl.tree.util.TreeResourceFactoryImpl;
import dsml.tree.Node;
import dsml.tree.Tree;
import dsml.tree.TreePackage;
import dsml.tree.impl.TreeFactoryImpl;
import dsml.tree.*;
import dsml.tree.util.*;

public class DSMLInstanceReader {

	private final static ResourceSet RESOURCE_SET=new ResourceSetImpl();;
	public static void main(String[] args)
	{
		Object rootModelElement= loadModel("models/My.tree");
		if(rootModelElement instanceof Tree)
		{
			Tree tree= (Tree) rootModelElement;
			Node root=tree.getRoot();
			printTreeNodesRec(root);
		}
	}
	public static void printTreeNodesRec(Node r)
	{
		System.out.println("Node: "+r.getLabel()+" Data: "+r.getData());
		for(Node n:r.getChildren())
		{
			if(n.getChildren().isEmpty())
				System.out.println("Node: "+n.getLabel()+" Data: "+n.getData());
			else
			{
				System.out.println("Node: "+n.getLabel()+" Data: "+n.getData());
				for(Node sub_n:n.getChildren())
					printTreeNodesRec(sub_n);
			}
		}
	}

	public static Object loadModel(String uri){
		URI modelUri = URI.createURI(uri);
		registerPackages(RESOURCE_SET);
		registerResourceFactories();
		String relPath = null;
		try {
			relPath = new File(".").getCanonicalPath();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		org.eclipse.emf.ecore.resource.Resource resource = null;
		try {	
			resource = RESOURCE_SET.getResource(modelUri, true);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		Object result;

		Tree _model = (Tree) EcoreUtil.getObjectByType(resource.getContents(), TreePackage.Literals.TREE);
		result = _model;
		if (_model == null) {
			result = resource.getContents().get(0);			
		}
		return result;
	}	
	
	private static void registerResourceFactories() 
	{
		Map extensionFactoryMap = org.eclipse.emf.ecore.resource.Resource.Factory.Registry.INSTANCE.getExtensionToFactoryMap();		  
		extensionFactoryMap.put("tree", new TreeResourceFactoryImpl());
	}

	private static void registerPackages(ResourceSet resourceSet) 
	{
		Map packageRegistry = resourceSet.getPackageRegistry();
		packageRegistry.put(EcorePackage.eNS_URI, EcorePackage.eINSTANCE);
		packageRegistry.put(TreePackage.eNS_URI, TreePackage.eINSTANCE);
	}
}
