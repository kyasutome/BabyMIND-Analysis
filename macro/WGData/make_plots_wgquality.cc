void make_plots_wgquality()
{
  TString filepath = "./process/5-WGClass/WGClass.root";
  TFile* fin = new TFile(filepath, "read");

  TCanvas *canvas = new TCanvas("canvas", "canvas", 1200, 800);
  canvas->SetGridx();
  canvas->SetGridy();
  canvas->cd();

  

}
