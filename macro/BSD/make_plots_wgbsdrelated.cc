
void make_plots_wgbsdrelated()
{
  TString filepath = "./result/BSD/WGAccumlated_pot.root";
  TFile* fin = new TFile(filepath, "read");
  TH2F *bsd_plot = (TH2F*)fin->Get("bsd_accumlated_plot");
  TH2F *wg_plot = (TH2F*)fin->Get("wg_accumlated_plot");

  TString bsdplotname, wgplotname;
  TString delivered, recorded;
  Double_t eff;

  TCanvas *canvas = new TCanvas("canvas", "canvas", 1200, 800);
  canvas->SetGridx();
  canvas->SetGridy();
  canvas->cd();

  bsd_plot->Draw("");
  wg_plot->Draw("same");

  TLegend* legend = new TLegend(0.10, 0.70, 0.70, 0.90);
  recorded = "10.727+e19";
  delivered = "10.814+e19";
  eff = 10.7267/10.814;
  bsdplotname.Form("Delivered P.O.T. (%s)", delivered.Data());
  wgplotname.Form("Recorded P.O.T. (%s)", recorded.Data());
  legend->AddEntry(bsd_plot,bsdplotname, "p");
  legend->AddEntry(wg_plot,wgplotname, "p");
  legend->Draw("same");
}
